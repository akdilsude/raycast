/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil < sakdil@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:23:55 by sakdil            #+#    #+#             */
/*   Updated: 2025/10/10 21:18:57 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_error_exit(t_game *game)
{
	(void)game;
	//free olcak
	exit(1);
}

void	game_edit(t_game *game)
{
	game->line_count = 0;
	game->player_direc = 0;
	game->map_start = 0;
}
