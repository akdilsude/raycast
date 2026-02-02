/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil < sakdil@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:53:07 by segunes           #+#    #+#             */
/*   Updated: 2025/10/10 22:36:59 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*validate_path(char *path)
{
	int	len;

	if (!path)
		return (NULL);
	len = ft_strlen(path);
	if (len < 4)
		return (NULL);
	if (!(path[len - 4] == '.' && path[len - 3] == 'x'
			&& path[len - 2] == 'p' && path[len - 1] == 'm'))
		return (NULL);
	if (access(path, F_OK | R_OK) != 0)
		return (NULL);
	return (path);
}

static char	*clean_end(char *str)
{
	int		len;
	char	*trim;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n'))
		len--;
	trim = ft_substr(str, 0, len);
	return (trim);
}

char	*find_path(char *input)
{
	int		i;
	char	*path;

	i = 0;
	while (input[i] && input[i] != ' ' && input[i] != '\t')
		i++;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (!input[i])
		return (NULL);
	path = clean_end(input + i);
	if (!path)
		return (NULL);
	if (!validate_path(path))
	{
		free(path);
		return (NULL);
	}
	return (path);
}
