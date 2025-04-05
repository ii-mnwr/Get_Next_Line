/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthodi <mthodi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:33:29 by mthodi            #+#    #+#             */
/*   Updated: 2024/01/28 12:20:54 by mthodi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_buffer(int fd, ssize_t *read_bytes, char *remainder, char *buffer)
{
	char	*temp;

	while (!ft_strchr(remainder, '\n') && *read_bytes > 0)
	{
		*read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (*read_bytes <= 0)
		{
			free(buffer);
			if (*read_bytes == 0)
				return (remainder);
			free(remainder);
			return (NULL);
		}
		buffer[*read_bytes] = '\0';
		temp = remainder;
		remainder = ft_strjoin(remainder, buffer);
		free(temp);
	}
	free(buffer);
	return (remainder);
}

char	*read_line(int fd, char *remainder)
{
	char	*buffer;
	ssize_t	read_bytes;

	read_bytes = 1;
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	remainder = read_buffer(fd, &read_bytes, remainder, buffer);
	return (remainder);
}

char	*new_line(char *remainder)
{
	int		i;
	char	*line;

	i = 0;
	while (remainder[i] != '\n' && remainder[i])
		i++;
	if (remainder[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*get_rest(char *remainder)
{
	int		i;
	char	*get_str;

	i = 0;
	while (remainder[i] != '\n' && remainder[i])
		i++;
	if (remainder[i] == '\n')
		i++;
	if (!remainder[i])
	{
		free (remainder);
		return (NULL);
	}
	get_str = ft_strdup(remainder + i);
	if (!get_str)
		return (NULL);
	free(remainder);
	return (get_str);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT32_MAX)
		return (NULL);
	remainder[fd] = read_line(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	line = new_line(remainder[fd]);
	remainder[fd] = get_rest (remainder[fd]);
	return (line);
}
