/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuster- <vfuster-@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:13:54 by vfuster-          #+#    #+#             */
/*   Updated: 2023/02/16 15:39:15 by vfuster-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/****************************************************************************
 * 
 * Macro BUFFER_SIZE definie avec #ifndef et #define
 * Si BUFFER_SIZE n'est pas deja defini, il sera defini a la valeur de
 * la constante BUFSIZ
 * BUFSIZ represente la taille du tampon de la bibliotheque standard
 * en octets
 * Si BUFFER_SIZE depasse la taille max autorisee, la macro est reinitialisee
 * a 0 avec #undef et #define. Cela permet d'eviter les erreurs de 
 * segmentation et de garantir aue la valeur de BUFFER_SIZE est valide
 *
 * *************************************************************************/

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

# if BUFFER_SIZE > 9223372036854775806
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

/* ---------- GNL ------------ */
char	*get_next_line(int fd);
void	ft_read_line(int fd, char **keep, char **tmp);
char	*ft_parse_line(char **keep, char **tmp);
char	*get_before_newline(const char *s);
char	*get_after_newline(const char *s);

/* ---------- UTILS ---------- */
int		contains_newline(const char *s);
char	*ft_strdup(const char *s1);
char	*join_strs(const char *s1, const char *s2);
void	*ft_malloc_zero(size_t count, size_t size);
void	ft_free_strs(char **str, char **str2, char **str3);

#endif
