/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil < sakdil@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:33:03 by sakdil            #+#    #+#             */
/*   Updated: 2025/10/11 14:53:40 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tabs_in_map(char **lines, t_game *game)
{
	int	y;
	int	x;

	y = game->map_start;
	while (y < game->map_start + game->y)
	{
		x = 0;
		while (lines[y][x])
		{
			if (lines[y][x] == '\t')
			{
				printf("Error\nTab var\n");
				free_error_exit(game);
			}
			x++;
		}
		y++;
	}
}

void	check_map_end(char **lines, t_game *game)
{
    int	i;
	int	end;

	end = game->map_start;
	while (end < game->line_count && !is_only_spaces(lines[end]))
		end++;

	end--;
	if (end < game->map_start)
	{
		printf("Error\nNo map found.\n");
		free_error_exit(game);
	}
	game->y = end - game->map_start + 1;
	i = end + 1;
	while (i < game->line_count)
	{
		if (!is_only_spaces(lines[i]))
		{
			printf("Error\nNothing is allowed after the map.\n");
			free_error_exit(game);
		}
		i++;
	}
}

void empty_line_inside_map(char **lines, t_game *game)
{
	int y;

	y = 0;
	while (y < game->y)
	{
		if (is_only_spaces(lines[game->map_start + y]))
		{
			printf("Error\nThere is empty space on the map.\n");
			free_error_exit(game);
		}
		y++;
	}
}

void	check_top_walls(char **lines, t_game *game)
{
	int		x;
	int		len;
	char	c;

	x = 0;
	len = line_len(lines[game->map_start]);
	while (x < len)
	{
		c = lines[game->map_start][x];
		if (c == '0' || check_nsew(c))
		{
			printf("Error\nTop edge not closed at x=%d\n", x + 1);
			free_error_exit(game);
		}
		x++;
	}
}

void	check_bottom_walls(char **lines, t_game *game)
{
	int		x;
	int		y;
	int		len;
	char	c;

	x = 0;
	y = game->y - 1;
	len = line_len(lines[game->map_start + y]);
	while (x < len)
	{
		c = lines[game->map_start + y][x];
		if (c == '0' || check_nsew(c))
		{
			printf("Error\nBottom edge not closed at x=%d\n", x + 1);
			free_error_exit(game);
		}
		x++;
	}
}
