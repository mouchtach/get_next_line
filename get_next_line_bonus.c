/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:54:47 by ymouchta          #+#    #+#             */
/*   Updated: 2024/12/03 11:02:07 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char **maloc)
{
	if (maloc && *maloc)
	{
		free(*maloc);
		*maloc = NULL;
	}
	return (NULL);
}

static void	ft_cpy(char **dst, char **src)
{
	int	i;

	i = 0;
	if (*dst && *src)
	{
		while ((*src)[i] && (*src)[i] != '\n')
		{
			(*dst)[i] = (*src)[i];
			i++;
		}
		if ((*src)[i] == '\n')
			(*dst)[i++] = '\n';
		(*dst)[i] = '\0';
	}
}

static char	*extra_line(char **line)
{
	int		i;
	char	*dst;
	char	*temp;

	i = 0;
	if (!line && !*line)
		return (NULL);
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if ((*line)[i] == '\n')
		i++;
	dst = malloc(i + 1);
	if (!dst)
		return (NULL);
	ft_cpy(&dst, line);
	temp = ft_strdup((*line) + i);
	if (!temp)
		return (ft_free(line), ft_free(&dst));
	ft_free(line);
	*line = temp;
	return (dst);
}

static char	*ft_get_line(int fd, char **line)
{
	char	*temp;
	char	*buffer;
	int		nb;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(line));
	while (1)
	{
		nb = read(fd, buffer, BUFFER_SIZE);
		if (nb < 0)
			return (ft_free(&buffer), ft_free(line));
		buffer[nb] = '\0';
		temp = ft_strjoin(*line, buffer);
		if (!temp)
			return (ft_free(&buffer), ft_free(line));
		ft_free(line);
		*line = temp;
		if (ft_strchr(*line, '\n') || nb == 0)
			break ;
	}
	ft_free(&buffer);
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*line[10240];
	char		*extra;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = ft_get_line(fd, &line[fd]);
	if (!line[fd])
		return (ft_free(&line[fd]));
	extra = extra_line(&line[fd]);
	if (!extra || ft_strlen(extra) == 0)
		return (ft_free(&extra), ft_free(&line[fd]));
	return (extra);
}