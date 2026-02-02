/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil < sakdil@student.42istanbul.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:36:45 by segunes           #+#    #+#             */
/*   Updated: 2025/10/11 15:00:29 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_join(char *str, char *buffer)
{
	int		i;
	int		j;
	char	*res;

	if (!str)
	{
		str = malloc(1);
		str[0] = '\0';
	}
	i = 0;
	j = 0;
	res = malloc(ft_strlen(str) + ft_strlen(buffer) + 1);
	if (res == NULL)
		return (NULL);
	while (str[j])
	{
		res[j] = str[j];
		j++;
	}
	while (buffer[i])
		res[j++] = buffer[i++];
	res[ft_strlen(str) + ft_strlen(buffer)] = '\0';
	free(str);
	return (res);
}

static char	*ft_line(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	ptr = malloc(i + 2);
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		ptr[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	*ft_new(char *str)
{
	int		j;
	int		i;
	char	*res;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	res = malloc((ft_strlen(str) - i) + 1);
	if (!res)
		return (NULL);
	i++;
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}

static char	*ft_buffer(int fd, char *str)
{
	char	*buffer;
	int		i;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	i = 1;
	while ((!str || ft_strchr(str, '\n') == 0) && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[i] = '\0';
		str = ft_join(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*ptr;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = ft_buffer(fd, str);
	if (!str)
		return (NULL);
	ptr = ft_line(str);
	str = ft_new(str);
	return (ptr);
}
