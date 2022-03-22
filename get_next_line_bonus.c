/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:06:32 by mchliyah          #+#    #+#             */
/*   Updated: 2021/12/04 16:19:31 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	strsearch(char *str, int c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(str);
	while (i < j && str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*not_found_n(char **str)
{
	char	*temp;

	if (*str != NULL && **str != '\0')
	{
		temp = *str;
		*str = NULL;
		return (temp);
	}
	else
	{
		free(*str);
		*str = NULL;
		return (NULL);
	}
}

char	*found_n(char **str)
{
	char	*temp;
	char	*line;
	int		i;

	i = strsearch(*str, '\n');
	temp = *str;
	line = ft_substr(*str, 0, i + 1);
	*str = ft_substr(*str, i + 1, ft_strlen(*str));
	free(temp);
	temp = NULL;
	return (line);
}

char	*full_static(char	*storage, char *rest, int fd, int read_return)
{
	while (strsearch(storage, '\n') == -1)
	{
		read_return = read(fd, rest, BUFFER_SIZE);
		if (read_return == 0 || read_return == -1)
			break ;
		rest[read_return] = '\0';
		storage = ft_strjoin(storage, rest);
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*rest;
	char		*line;
	int			read_return;

	read_return = 0;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage[fd])
	{
		storage[fd] = ft_strdup("");
		if (!storage[fd])
			return (NULL);
	}
	rest = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	storage[fd] = full_static(storage[fd], rest, fd, read_return);
	free (rest);
	if (strsearch(storage[fd], '\n') == -1)
		return (not_found_n(&storage[fd]));
	line = found_n(&storage[fd]);
	return (line);
}
