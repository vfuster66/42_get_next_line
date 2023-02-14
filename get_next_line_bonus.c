/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuster- <vfuster-@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:51:36 by vfuster-          #+#    #+#             */
/*   Updated: 2023/02/13 11:11:54 by vfuster-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	get_len_of_line(char *buffer)
{
	size_t	len;

	len = 0;
	while (buffer[len] != '\n' && buffer[len] != '\0')
		len++;
	if (buffer[len] == '\n')
		len++;
	return (len);
}

static ssize_t	get_read(int fd, char **buffer)
{
	ssize_t	len_read;

	free(*buffer);
	*buffer = malloc(sizeof(**buffer) * (BUFFER_SIZE + 1));
	if (*buffer == NULL)
		return (0);
	len_read = read(fd, *buffer, BUFFER_SIZE);
	if (len_read <= 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
	else
		(*buffer)[len_read] = 0;
	return (len_read);
}

static char	*get_line(char **buffer, int fd, int *nl_found)
{
	ssize_t	len_read;
	char	*line;
	size_t	len_line;
	char	*buff_tmp;

	if (*buffer == NULL || ft_strlen(*buffer) == 0)
	{
		len_read = get_read(fd, buffer);
		if (len_read <= 0)
			return (NULL);
	}
	len_line = get_len_of_line(*buffer);
	if ((*buffer)[len_line - 1] == '\n')
		*nl_found = 1;
	line = malloc(len_line + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, *buffer, len_line + 1);
	buff_tmp = ft_strdup((*buffer) + len_line);
	if (buff_tmp == NULL)
		return (NULL);
	free(*buffer);
	*buffer = buff_tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line_old;
	int			nl_found;
	char		*line;
	char		*new_line;

	if (fd < 0)
		return (NULL);
	nl_found = 0;
	line = get_line(&buffer[fd], fd, &nl_found);
	if (line == NULL)
		return (NULL);
	while (nl_found == 0)
	{
		new_line = get_line(&buffer[fd], fd, &nl_found);
		if (new_line == NULL)
			return (line);
		line_old = line;
		line = ft_strjoin(line, new_line);
		free(new_line);
		free(line_old);
	}
	return (line);
}
