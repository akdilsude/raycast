/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil < sakdil@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:35:26 by sakdil            #+#    #+#             */
/*   Updated: 2025/10/11 16:58:08 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	name_control(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '.')
			i++;
		else
			break;
	}
	if ((str[i] == '.' && str[i - 1] == '/') || (ft_strcmp(str + i, ".cub") != 0))
	{
		printf("Error\nInvalid map file extension.\n");
		// free_exit(list);
	}
}

static void	check_surround(char **lines, int x, int y, t_game *game)
{
	int	curr_len;

	curr_len = line_len(lines[game->map_start + y]);
	if (y == 0 || x >= line_len(lines[game->map_start + y - 1])
		|| lines[game->map_start + y - 1][x] == ' ' )
	{ //üst
		printf("Error\nMap not closed (above).\n");
		free_error_exit(game);
	}
	if (y == game->y - 1 || x >= line_len(lines[game->map_start + y + 1])
		|| lines[game->map_start + y + 1][x] == ' ')
	{ //alt
		printf("Error\nMap not closed (below).\n");
		free_error_exit(game);
	}
	if (x == 0 || lines[game->map_start + y][x - 1] == ' ')
	{ //sol
		printf("Error\nMap not closed (left).\n");
		free_error_exit(game);
	}
	if (x + 1 >= curr_len || lines[game->map_start + y][x + 1] == ' ')
	{ //sağ
		printf("Error\nMap not closed (right).\n");
		free_error_exit(game);
	}
}

void	check_zero(char **lines, t_game *game)
{
	int		x;
	int		y;
	int		curr_len;
	char	c;

	y = 0;
	while (y < game->y)
	{
		x = 0;
		curr_len = line_len(lines[game->map_start + y]);
		while (x < curr_len)
		{
			c = lines[game->map_start + y][x];
			if (c == '0' || check_nsew(c))
				check_surround(lines, x, y, game);
			x++;
		}
		y++;
	}
}
