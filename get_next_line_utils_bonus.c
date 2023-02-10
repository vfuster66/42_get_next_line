/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuster- <vfuster-@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:50:23 by vfuster-          #+#    #+#             */
/*   Updated: 2023/02/10 07:53:36 by vfuster-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/// @brief calculer la longueur d'une chaine de caracteres sans \0
/// @param s 
/// @return Nombre de caracteres de la chaine
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

/// @brief Copie une chaine de caractere garantissant la longueur max pour dst
/// @param dst pointeur vers la destination
/// @param src pointeur vers la source
/// @param size taille du buffer de destination
/// @return Longueur de la chaine src sans \0
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	i = 0;
	if (size > len_src)
	{
		while (i < len_src)
			dst[i++] = 0;
		ft_memcpy(dst, src, len_src);
	dst[len_src] = 0;
	}
	else if (size != 0)
	{
		while (i < (size - 1))
			dst[i++] = 0;
		if (ft_strlen(src) < (size - 1))
			ft_memcpy(dst, src, ft_strlen(src));
		else
			ft_memcpy(dst, src, (size - 1));
		dst[size - 1] = 0;
	}
	return (len_src);
}

/// @brief Dupliquer une chaine de caractere
/// @param s Pointeur sur la chaine de caracteres
/// @return Pointeur sur nouvelle chaine dupliquee depuis s
char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	str = malloc(sizeof(*str) * len + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s, len);
	str[len] = 0;
	return (str);
}

/// @brief Joint 2 chaines de caracteres en une seule
/// @param s1 Pointeur sur premiere chaine
/// @param s2 Pointeur sur deuxieme chaine
/// @return Nouvelle chaine contenant les 2 chaines
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*str;
	char	*ptr;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(*str) * len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = 0;
	ptr = str;
	ft_memcpy(ptr, s1, ft_strlen(s1) + 1);
	ptr = ptr + ft_strlen(s1);
	ft_memcpy(ptr, s2, ft_strlen(s2) + 1);
	return (str);
}