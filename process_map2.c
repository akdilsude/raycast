/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil < sakdil@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:46:26 by sakdil            #+#    #+#             */
/*   Updated: 2025/10/11 16:57:26 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	continue_side_walls(char **lines, t_game *game, int y)
{
	int		len;
	int		i;
	char	*row;

	i = 0;
	row = lines[game->map_start + y];
	len = line_len(row);
	while (i < len && row[i] == ' ')
			i++;
	while (len > 0 && row[len - 1] == ' ')
		len--;
	if (i < len)
	{
		if (row[i] != '1')
		{
			printf("Error\nLeft edge not closed at y=%d\n", y + 1);
			free_error_exit(game);
		}
		if (row[len - 1] != '1')
		{
			printf("Error\nRight edge not closed at y=%d\n", y + 1);
			free_error_exit(game);
		}
	}
}

void	check_side_walls(char **lines, t_game *game)
{
	int	y;

	y = 1;
	while (y < game->y - 1)
	{
		continue_side_walls(lines, game, y);
		y++;
	}
}

static void	error_check_map(char c, t_game *game)
{
	if (c == '\t')
	{
		printf("Error\nTab var\n");
		free_error_exit(game);
	}
	if (!is_map_char(c))
	{
		printf("Error\nInvalid character '%c'.\n", c);
		free_error_exit(game);
	}
}

void	check_map(char **lines, t_game *game)
{
	int		y;
	int		x;
	int		len;
	char	c;

	y = 0;
	while (y < game->y)
	{
		x = 0;
		len = line_len(lines[game->map_start + y]);
		while (x < len)
		{
			c = lines[game->map_start + y][x];
			error_check_map(c, game); 
			x++;
		}
		y++;
	}
}

char	**build_map(char **line, t_game * game)
{
	int	y;

	y = 0;
	game->map = (char **)malloc(sizeof(char *) * (game->y + 1));
	if (!game->map)
	{
		printf("Error\nFailed map.\n");
		free_error_exit(game);
	}
	while (y < game->y)
	{
		game->map[y] = ft_strdup(line[game->map_start + y]);
		if (!game->map[y])
		{
			printf("Error\nFailed map.\n");
			//double_free(game->map);
			free_error_exit(game);
		}
		y++;
	}
	game->map[y] = NULL;
	return (game->map);
}
