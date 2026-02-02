/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil <sakdil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:44:25 by sakdil            #+#    #+#             */
/*   Updated: 2026/02/02 15:01:42 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= game->win_x || y >= game->win_y)
		return ;
	dst = game->image.pixels + (y * game->image.line_len + x * (game->image.bits_per_pixel / 8));
	*(int*)dst = color;
}

void	draw_vertical_line(t_game *game, int x)
{
	int	y;
	int	floor_color;
	int	ceiling_color;
	int	wall_color;

	y = 0;
	floor_color = create_color(game->floor_r, game->floor_g, game->floor_b);
	ceiling_color = create_color(game->ceiling_r, game->ceiling_g, game->ceiling_b);
	if (game->ray.side == 0)
		wall_color = 0xBB0000; // Koyu Kırmızı
	else
		wall_color = 0xFF0000; // Açık Kırmızı
	while (y < game->ray.draw_start)
		pixel_put(game, x, y++, ceiling_color);
	while (y < game->ray.draw_end)
		pixel_put(game, x, y++, wall_color);
	while (y < game->win_y)
		pixel_put(game, x, y++, floor_color);
}
