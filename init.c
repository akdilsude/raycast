/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segunes <segunes@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:31:48 by sakdil            #+#    #+#             */
/*   Updated: 2026/02/04 01:26:59 by segunes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_mlx(t_game *game)
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

static int close_window(t_game *game)
{
	// freeleri buraya at
	printf("Existing the game....\n");
	free_error_exit(game);
	return (0);
}

int key_press(int keycode, t_game *game) // tuşa basıldığında değerleri 1 e dönüşecek basıldığına dair
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 119)
		game->key_w = 1;
	if (keycode == 115)
		game->key_s = 1;
	if (keycode == 97)
		game->key_a = 1;
	if (keycode == 100)
		game->key_d = 1;
	if (keycode == 65361) // Sol Ok - Sola Dön
		game->key_left = 1;
	if (keycode == 65363) // Sağ Ok - Sağa Dön
		game->key_right = 1;
	return (0);
}

int key_release(int keycode, t_game *game) // tuşa basılma kesildiğinde 0 a dönecek
{
	if (keycode == 119)
		game->key_w = 0;
	if (keycode == 115)
		game->key_s = 0;
	if (keycode == 97)
		game->key_a = 0;
	if (keycode == 100)
		game->key_d = 0;
	if (keycode == 65361)
		game->key_left = 0;
	if (keycode == 65363)
		game->key_right = 0;
	return (0);
}

static int game_loop(t_game *game)
{
	if (game->key_w)
		move_w_s(game, 1);
	if (game->key_s)
		move_w_s(game, -1);
	if (game->key_a)
		move_a_d(game, -1);
	if (game->key_d)
		move_a_d(game, 1);
	if (game->key_left)
		rotate_player(game, -1);
	if (game->key_right)
		rotate_player(game, 1);

	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img, 0, 0);
	return (0);
}

void game_start(t_game *game)
{
	game->key_w = 0;
	game->key_s = 0;
	game->key_a = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;

	init_mlx(game);
	load_textures(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);	// KeyPress (2)
	mlx_hook(game->win, 3, 1L << 1, key_release, game); // KeyRelease (3)
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}