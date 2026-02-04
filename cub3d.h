/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segunes <segunes@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:01:46 by segunes           #+#    #+#             */
/*   Updated: 2026/02/03 16:22:16 by segunes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> 
# include <stdbool.h>
# include "minilibx-linux/mlx.h"
# include <math.h> //fabs için

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#endif

#  define WINDOW_WIDTH 1280
#  define WINDOW_HEIGHT 720
#  define MOVE_SPEED 0.1
#  define ROT_SPEED 0.05

typedef struct s_control
{
	int	is_no;
	int	is_so;
	int	is_we;
	int	is_ea;
	int	is_floor;
	int	is_ceiling;
}	t_control;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_distance;
	int		step_x;
	int		step_y;
	int		has_hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_image
{
	void	*img;           // İmajın MLX işaretçisi (img)
	char	*pixels;        // Piksellerin ham verisi 
	int		bits_per_pixel; // Renk derinliği
	int		line_len;      // Bir satırın byte uzunluğu 
	int		byte_order; 	// Byte sıralaması
	int		width;
	int		height;
}	t_image;

typedef struct s_game
{
	int		fd;
	int		x; //kullanmıyorum şimdilik
	int		y;
	double	player_x; //raycastte ondalıklı syılarla uğraşıcağımız için double yaptım bunları.
	double	player_y;
	double	vec_x;
	double	vec_y;
	double	plane_x;
	double	plane_y;
	char	player_direc;
	int		map_start;
	int		line_count;
	char	*line_map;
	char	**map;

	char	*north;
	char	*south;
	char	*west;
	char	*east;

	int		floor_r;
	int		floor_g;
	int		floor_b;

	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;


	void	*mlx;
	void	*win;
	void	*img; //t_image yapısına taşıdım
	int		win_x;
	int		win_y;

	int key_w;
    int key_s;
    int key_a;
    int key_d;
    int key_left;
    int key_right;

	t_control	control;
	t_ray		ray;
	t_image		textures[4];
	t_image		image;
	
}	t_game;

char	*find_path(char *input);
bool	handle_no(char *line, t_game *game);
bool	handle_so(char *line, t_game *game);
bool	handle_we(char *line, t_game *game);
bool	handle_ea(char *line, t_game *game);
int		is_all_set(t_game *game);
int		control_identifier(char **lines, t_game *game);
void	start_control_value(t_game *game);
void	open_map(char *argv, t_game *game);
void	tabs_in_map(char **lines, t_game *game);
void	check_map_end(char **lines, t_game *game);
void	empty_line_inside_map(char **lines, t_game *game);
void	name_control(char *str);
void	game_edit(t_game *list);
int		is_only_spaces(char *str);
char	**build_map(char **line, t_game * game);
bool	handle_floor(t_game *game);
bool	handle_ceiling(t_game *game);
char	*get_next_line(int fd);
void	free_error_exit(t_game *game);
int		line_len(char *str);
void	check_zero(char **lines, t_game *game);
void	check_map(char **lines, t_game *game);
int		check_color(char *line, t_game *game);
int		check_nsew(char c);
void	check_top_walls(char **lines, t_game *game);
void	check_bottom_walls(char **lines, t_game *game);
void	check_side_walls(char **lines, t_game *game);
int		is_map_char(char c);

void	game_start(t_game *game);
int		create_color(int r, int g, int b);
//void	draw_pixel_to_image(int x, int y, int color, t_game *game); //YAZILACAK
void load_textures(t_game *game);


void	draw_vertical_line(t_game *game, int x);
int	raycasting(t_game *game);

void	rotate_player(t_game *game, int i);
void	move_w_s(t_game *game, int direction);
void	move_a_d(t_game *game, int direction);

#endif