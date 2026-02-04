/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segunes <segunes@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:44:25 by sakdil            #+#    #+#             */
/*   Updated: 2026/02/04 01:25:22 by segunes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void load_textures(t_game *game)
{
	char *path[4];
	int i;

	i = 0;
	path[0] = game->north;
	path[1] = game->south;
	path[2] = game->east;
	path[3] = game->west;

	while (i < 4)
	{
		if (!path[i]) {
            printf("Error\nTexture path is NULL for index %d\n", i);
            exit(1);
        }
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, path[i], &game->textures[i].width, &game->textures[i].height);
		if (!game->textures[i].img)
		{
			printf("Error\nCould not load texture.");
			free_error_exit(game);
		}
		game->textures[i].pixels = mlx_get_data_addr(game->textures[i].img,
													 &game->textures[i].bits_per_pixel,
													 &game->textures[i].line_len,
													 &game->textures[i].byte_order);
		i++;
	}
}

int create_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void pixel_put(t_game *game, int x, int y, int color)
{
	char *dst;

	if (x < 0 || y < 0 || x >= game->win_x || y >= game->win_y)
		return;
	dst = game->image.pixels + (y * game->image.line_len + x * (game->image.bits_per_pixel / 8));
	*(int *)dst = color;
}

int texture_index(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.dir_x > 0)
			return (3);
		return (2);
	}
	else
	{
		if (game->ray.dir_y > 0)
			return (1);
		return (0);
	}
}

void draw_vertical_line(t_game *game, int x)
{
    int y;
    int tex_idx;
    double wall_x;
    int tex_x;
    double step;
    double tex_pos;

    tex_idx = texture_index(game);

    // wall_x hesaplama
    if (game->ray.side == 0)
        wall_x = game->player_y + game->ray.wall_distance * game->ray.dir_y;
    else
        wall_x = game->player_x + game->ray.wall_distance * game->ray.dir_x;
    wall_x -= floor(wall_x);

    //  tex_x hesaplama ve sınır kontrolü 
    tex_x = (int)(wall_x * (double)game->textures[tex_idx].width);
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= game->textures[tex_idx].width) 
        tex_x = game->textures[tex_idx].width - 1;

    //  Ölçekleme ve başlangıç noktası
    step = 1.0 * game->textures[tex_idx].height / game->ray.line_height;
    // tex_pos'un başlangıcını duvarın ekran dışına taşma durumuna göre koru
    tex_pos = (game->ray.draw_start - game->win_y / 2 + game->ray.line_height / 2) * step;
    if (tex_pos < 0) tex_pos = 0;

    y = 0;
    while (y < game->win_y)
    {
        if (y < game->ray.draw_start) //tavan
            pixel_put(game, x, y, create_color(game->ceiling_r, game->ceiling_g, game->ceiling_b));
        else if (y >= game->ray.draw_start && y < game->ray.draw_end)//duvar
        {
            //tex_y hesapla ve texture sınırları içinde tutma
            int tex_y = (int)tex_pos % game->textures[tex_idx].height;
            tex_pos += step;

            //  Bellek erişimi 
            int color = *(int *)(game->textures[tex_idx].pixels + 
                        (tex_y * game->textures[tex_idx].line_len + 
                         tex_x * (game->textures[tex_idx].bits_per_pixel / 8)));
            
            pixel_put(game, x, y, color);
        }
        else //taban
            pixel_put(game, x, y, create_color(game->floor_r, game->floor_g, game->floor_b));
        y++;
    }
}