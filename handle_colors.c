/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segunes <segunes@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:13:45 by sakdil            #+#    #+#             */
/*   Updated: 2025/10/11 16:52:36 by segunes          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

bool	handle_floor(t_game *game)
{
	if (game->control.is_floor)
		return (printf("Error\nDuplicate F identifier.\n"), false);
	game->control.is_floor = 1;
	return (true);
}

bool	handle_ceiling(t_game *game)
{
	if (game->control.is_ceiling)
		return (printf("Error\nDuplicate C identifier.\n"), false);
	game->control.is_ceiling = 1;
	return (true);
}

int	check_color_number(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	while (rgb[i] != NULL)
	{
		j = 0;
		while (rgb[i][j] != '\0')
		{
			if (!ft_isdigit(rgb[i][j]))
			{
				printf("invalid character");
				return (-1);
			}
			j++;
		}
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
		{
			printf("invalid number");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_color(char *line, t_game *game)
{
	int count;
	char **rgb;
	char *str;
	char *tmp;
	size_t i;
	int j;

	i = 0;
	j = 0;
	count = 0;
	str = ft_strtrim(line + 1, " \t\n");
	tmp = malloc(ft_strlen(str) + 1);
	if(!tmp)
	{
		printf("Error\nMemory allocation failed\n");
		free(str);
		return(-1);//değiştirilebilir	
	}
	if (!str)
	{
		printf("Error\n");
		return (-1);
	}
	while(i < ft_strlen(str))
	{
		if(str[i] != ' ' && str[i] != '\t')
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	rgb = ft_split(tmp, ',');
	if (!rgb)
	{
		printf("Error\n");
		return (-1);
	}
	while (rgb[count] != NULL)
		count++;
	if (count != 3)
	{
		printf("invalid number");
		return (-1);
	}
	if (check_color_number(rgb) == -1)
		return (-1);
	if (line[0] == 'F')
	{
		game->floor_r = ft_atoi(rgb[0]);
		game->floor_g = ft_atoi(rgb[1]);
		game->floor_b = ft_atoi(rgb[2]);
	}
	else if (line[0] == 'C')
	{
		game->ceiling_r = ft_atoi(rgb[0]);
		game->ceiling_g = ft_atoi(rgb[1]);
		game->ceiling_b = ft_atoi(rgb[2]);
	}
	return (0);
}

