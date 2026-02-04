/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segunes <segunes@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:36:17 by sakdil            #+#    #+#             */
/*   Updated: 2026/02/04 01:21:32 by segunes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_ray(t_game *game, int x)
{
	game->ray.camera_x = 2 * x / (double)game->win_x - 1;
	game->ray.dir_x = game->vec_x + game->plane_x * game->ray.camera_x;
	game->ray.dir_y = game->vec_y + game->plane_y * game->ray.camera_x;
	game->ray.map_x = (int)game->player_x;
	game->ray.map_y = (int)game->player_y;

	game->ray.delta_dist_x = fabs(1 / game->ray.dir_x);
	game->ray.delta_dist_y = fabs(1 / game->ray.dir_y);
}

static void calculate_step(t_game *game)
{
	if (game->ray.dir_x < 0)
	{
		game->ray.step_x = -1; // Sola git
		game->ray.side_dist_x = (game->player_x - game->ray.map_x) * game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1; // Sağa git
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player_x) * game->ray.delta_dist_x;
	}
	if (game->ray.dir_y < 0)
	{
		game->ray.step_y = -1; // Yukarı git
		game->ray.side_dist_y = (game->player_y - game->ray.map_y) * game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1; // Aşağı git
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player_y) * game->ray.delta_dist_y;
	}
}

static void search_for_wall(t_game *game)
{
	game->ray.has_hit = 0;
	while (game->ray.has_hit == 0)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}

		if (game->ray.map_y < 0 || game->ray.map_y >= game->y ||
			game->ray.map_x < 0 || game->ray.map_x >= (int)ft_strlen(game->map[game->ray.map_y]))
			break;
		if (game->map[game->ray.map_y][game->ray.map_x] == '1')
			game->ray.has_hit = 1;
	}
}

static void calc_wall_height(t_game *game)
{
	// dda algoritması burası önemli dik duvar mesafe formülü mesefayi doğru bulmak için
	// ve balık gözü efektini önlemek için eğer oyuncudan giden ışının sadece hipotenüsünü alsaydık duvarlar düz değil 
	// bir kürenin içindeymiş gibi kavisli görünürdü bu formül ışının sadece bakış yönüne dik olan bileşenini hesaplar
	//ilkinde sadece tuşa basınca bir kare çiziliyordu raycasting matematiğinde hatalar olsa bile ekran saniyede sadece 
	//1-2 kez güncellendiği için bu hatalar göze batmıyordu ve görünmüyordu
	//game_loop sistemine geçince motor saniyede 60 kareden fazla çizmeye başladı. matematikteki o küçük sapmalar saniyede 60 kez üst üste binince mlxi kilitledi. 
	//duvar boyu bir anda sonsuza fırlıyor textures koordinatları (tex_x, tex_y) bellek sınırlarını aşıyordu
	// bu sorunu da aşağıda ki Perpendicular Wall Distance (Dik Duvar Mesafesi) formülü ile çözdük
	if (game->ray.side == 0)
		game->ray.wall_distance = (game->ray.map_x - game->player_x + (1 - game->ray.step_x) / 2) / game->ray.dir_x;
	else
		game->ray.wall_distance = (game->ray.map_y - game->player_y + (1 - game->ray.step_y) / 2) / game->ray.dir_y;

	if (game->ray.wall_distance <= 0)
		game->ray.wall_distance = 0.1;
	// 2. Duvar yüksekliği (Ekran yüksekliği / Mesafe)
	game->ray.line_height = (int)(game->win_y / game->ray.wall_distance);
	// 3. Çizimin başlangıç noktası (Ekranın ortasına göre hizala)
	game->ray.draw_start = -game->ray.line_height / 2 + game->win_y / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	// 4. Çizimin bitiş noktası
	game->ray.draw_end = game->ray.line_height / 2 + game->win_y / 2;
	if (game->ray.draw_end >= game->win_y)
		game->ray.draw_end = game->win_y - 1;
}

int raycasting(t_game *game)
{
	int x;

	x = 0;
	// Ekran genişliği boyunca (0'dan 1280'e kadar) döngü
	while (x < game->win_x)
	{
		init_ray(game, x);			 // Değerleri hazırla
		calculate_step(game);		 // Yönü belirle
		search_for_wall(game);		 // Duvarı bulana kadar git
		calc_wall_height(game);		 // Yüksekliği hesapla
		draw_vertical_line(game, x); // Ekrana (buffer'a) çiz
		x++;
	}
	return (0);
}
