/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil <sakdil@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:24:19 by sakdil            #+#    #+#             */
/*   Updated: 2025/12/02 12:33:43 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_only_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

int	is_all_set(t_game *game)
{
	if (game->control.is_no && game->control.is_so && game->control.is_we 
			&& game->control.is_ea && game->control.is_floor && game->control.is_ceiling)
		return (1);
	return (0);
}

void	start_control_value(t_game *game)
{
	game->control.is_no = 0;
	game->control.is_so = 0;
	game->control.is_we = 0;
	game->control.is_ea = 0;
	game->control.is_floor = 0;
	game->control.is_ceiling = 0;
}

int check_nsew(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == '\n'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
