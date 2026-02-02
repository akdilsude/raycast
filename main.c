/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil <sakdil@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:57:15 by segunes           #+#    #+#             */
/*   Updated: 2025/12/02 12:03:30 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*list;

	list = (t_game *)malloc(sizeof(t_game));
	if (!list)
		return (write(1, "Error: Malloc failed\n", 21), 0);
	game_edit(list);
	if (argc == 2 && argv[1] && argv[1][0] != '.')
	{
		name_control(argv[1]);
		open_map(argv[1], list);
	// 	if (list->x > 59 || list->y > 32)
	// 	{
	// 		write(1, "Error\nMap size exceeds limits (max 59x32).\n", 43);
	// 		free_exit(list);
	// 	}
		game_start(list);
	// }
	// else
	// {
	// 	write(1, "Error\nInvalid arguments.\n", 25);
	// 	main_finish(list);
	}
	return (0);
}
