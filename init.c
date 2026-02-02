/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil <sakdil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:31:48 by sakdil            #+#    #+#             */
/*   Updated: 2026/02/02 15:14:14 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error\nMLX build failed.\n");
		free_error_exit(game);
	}
	game->win_x = WINDOW_WIDTH;
	game->win_y = WINDOW_HEIGHT;
	game->win = mlx_new_window(game->mlx, game->win_x, game->win_y, "Cub3d");
	if (!game->win)
	{
		printf("Error\nFailed to create window.\n");
		free_error_exit(game);
	}
	game->image.img = mlx_new_image(game->mlx, game->win_x, game->win_y);
	if (!game->image.img)
	{
		printf("Error\nFailed to create image.\n");
		free_error_exit(game);
	}
	game->image.pixels = mlx_get_data_addr(game->image.img,
			&game->image.bits_per_pixel,
			&game->image.line_len,
			&game->image.byte_order);
}

static int	close_window(t_game *game)
{
	//freeleri buraya at
	printf("Exiting the game....\n");
	free_error_exit(game);
	return (0);	
}

static int	key_control(int keycode, t_game *game)
{
	if (keycode == 65307) 
	{
		close_window(game);
		return (0);
	}
	if (keycode == 119) // W - İleri
		move_w_s(game, 1);
	else if (keycode == 115) // S - Geri
		move_w_s(game, -1);
	else if (keycode == 97)  // A - Sola Kay
		move_a_d(game, -1);
	else if (keycode == 100) // D - Sağa Kay
		move_a_d(game, 1);
	else if (keycode == 65361) // Sol Ok - Sola Dön
		rotate_player(game, -1);
	else if (keycode == 65363) // Sağ Ok - Sağa Dön
		rotate_player(game, 1);
	return (0);
}

static int	game_loop(t_game *game)
{
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win,
		game->image.img, 0, 0);
	return (0);
}

void	game_start(t_game *game)
{
	init_mlx(game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, key_control, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
