/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuster- <vfuster-@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:24:28 by vfuster-          #+#    #+#             */
/*   Updated: 2023/02/09 14:42:08 by vfuster-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	is_new_line(t_line *cache);
static void	read_line(t_line **cache, int fd);
static void	create_line(t_line *cache, char **line);
static void	refactor_line(t_line **cache);

static int	is_new_line(t_line *cache)
{
	int	i;

	cache = ft_lstlast(cache);
	if (!cache)
		return (0);
	i = 0;
	while (cache->content[i])
	{
		if (cache->content[i] == '\n')
			return (1);
		i++;
	}
	cache->lenght = i;
	return (0);
}

static void	read_line(t_line **cache, int fd)
{
	int		output;
	char	*buffer;
	t_line	*new_node;

	output = 0;
	while (!is_new_line(*cache))
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(*buffer));
		new_node = ft_lstnew(buffer);
		if (!new_node)
		{
			free(buffer);
			return ;
		}
		output = read(fd, new_node->content, BUFFER_SIZE);
		if (output == 0 || output == -1)
		{
			free(buffer);
			free(new_node);
			return ;
		}
		ft_lstadd_back(cache, new_node);
	}
	return ;
}

static void	create_line(t_line *cache, char **line)
{
	int		ln_size;
	int		i;
	t_line	*temp;

	temp = cache;
	ln_size = 0;
	while (temp)
	{
		ln_size = ln_size + temp->lenght;
		temp = temp->next;
	}
	if (!ln_size)
		return ;
	*line = malloc(sizeof(**line) * (ln_size + 1));
	if (!line)
		return ;
	ln_size = 0;
	while (cache && cache->content)
	{
		i = 0;
		while (cache->content[i] && i < cache->lenght)
			(*line)[ln_size++] = cache->content[i++];
		cache = cache->next;
	}
	(*line)[ln_size] = '\0';
}

static void	refactor_line(t_line **cache)
{
	t_line	*temp;
	t_line	*new_node;
	char	*content;
	int		i;
	int		size;

	size = 0;
	temp = ft_lstlast(*cache);
	if (!temp)
		return ;
	content = temp->content;
	size = temp->lenght;
	temp->content = NULL;
	free(temp);
	i = 0;
	if (content[size] != '\0')
	{
		while (content[size])
			content[i++] = content[size++];
		content[i] = '\0';
		new_node = ft_lstnew(content);
		ft_lstadd_back(cache, new_node);
	}
	else
		free(content);
}

char	*get_next_line(int fd)
{
	static t_line	*cache;
	char			*line;
	t_line			*temp;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!cache)
		cache = ft_lstnew(NULL);
	temp = cache;
	while (temp->next)
		temp = temp->next;
	read_line(temp, fd);
	if (!temp->content)
		return (NULL);
	create_line(temp, &line);
	refactor_line(temp);
	return (line);
}
