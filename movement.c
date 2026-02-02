/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil <sakdil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:13:50 by sakdil            #+#    #+#             */
/*   Updated: 2026/02/02 15:08:25 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_game *game, int i)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED * i;

	// 1. Oyuncunun Ana Yönünü (vec) Döndür
	old_dir_x = game->vec_x;
	game->vec_x = game->vec_x * cos(rot_speed) - game->vec_y * sin(rot_speed);
	game->vec_y = old_dir_x * sin(rot_speed) + game->vec_y * cos(rot_speed);

	// 2. Kamera Düzlemini (plane) Döndür
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(rot_speed) - game->plane_y * sin(rot_speed);
	game->plane_y = old_plane_x * sin(rot_speed) + game->plane_y * cos(rot_speed);
}

void	move_w_s(t_game *game, int direction)
{
	double	new_x;
	double	new_y;

	new_x = game->player_x + (game->vec_x * MOVE_SPEED * direction);
	new_y = game->player_y + (game->vec_y * MOVE_SPEED * direction);

	if (game->map[(int)game->player_y][(int)new_x] != '1')
		game->player_x = new_x;

	if (game->map[(int)new_y][(int)game->player_x] != '1')
		game->player_y = new_y;
}

void	move_a_d(t_game *game, int direction)
{
	double	new_x;
	double	new_y;

	new_x = game->player_x + (game->plane_x * MOVE_SPEED * direction);
	new_y = game->player_y + (game->plane_y * MOVE_SPEED * direction);

	if (game->map[(int)game->player_y][(int)new_x] != '1')
		game->player_x = new_x;

	if (game->map[(int)new_y][(int)game->player_x] != '1')
		game->player_y = new_y;
}

