/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuster- <vfuster-@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:24:14 by vfuster-          #+#    #+#             */
/*   Updated: 2023/02/09 13:51:01 by vfuster-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_line
{
	char			*content;
	int				lenght;
	struct s_line	*next;
}					t_line;

char	*get_next_line(int fd);
t_line	*ft_lstnew(char *content);
t_line	*ft_lstlast(t_line *lst);
void	ft_lstclear(t_line **lst, void (*del)(void *));
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_lstadd_back(t_line **lst, t_line *new);

#endif
