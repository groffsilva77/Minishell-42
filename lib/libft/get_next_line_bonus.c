/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:01:44 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/23 13:32:29 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_line(int fd)
{
	int		bytes_read;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free(buffer), NULL);
	buffer[bytes_read] = '\0';
	return (buffer);
}

static char	*ft_find_and_extract(char **buffer)
{
	char	*line;
	char	*newline_pos;
	char	*rest;

	if (!buffer || !*buffer || !**buffer)
		return (NULL);
	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos)
	{
		line = ft_substr(*buffer, 0, newline_pos - *buffer + 1);
		if (!line)
			return (free(*buffer), *buffer = NULL, NULL);
		rest = ft_strdup(newline_pos + 1);
		if (!rest)
			return (free(line), free(*buffer), *buffer = NULL, NULL);
		free(*buffer);
		*buffer = rest;
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

static char	*ft_upbuffer(char *buffer, const char *temp)
{
	char	*new_buff;

	if (!temp)
		return (buffer);
	if (!buffer)
		return (ft_strdup(temp));
	new_buff = ft_strjoin(buffer, temp);
	if (!new_buff)
		return (free(buffer), NULL);
	free(buffer);
	return (new_buff);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024] = {NULL};
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr(buffer[fd], '\n'))
	{
		temp = ft_read_line(fd);
		if (!temp)
			return (free(buffer[fd]), buffer[fd] = NULL, NULL);
		if (!*temp)
		{
			free(temp);
			break ;
		}
		buffer[fd] = ft_upbuffer(buffer[fd], temp);
		free(temp);
		if (!buffer[fd])
			return (NULL);
	}
	line = ft_find_and_extract(&buffer[fd]);
	if (!line)
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	return (line);
}

/*#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test_file.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		return (EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	if (close(fd) < 0)
	{
		perror("Erro ao fechar o arquivo");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}*/
