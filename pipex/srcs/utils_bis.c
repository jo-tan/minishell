/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:09:15 by aauthier          #+#    #+#             */
/*   Updated: 2022/02/01 18:11:44 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s_char;

	i = -1;
	s_char = (char *)s;
	if (c == '\0')
		return (&s_char[ft_strlen(s)]);
	while (s_char[++i])
		if (s_char[i] == (char)c)
			return (&s_char[i]);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_char;
	unsigned char	*s2_char;

	i = 0;
	s1_char = (unsigned char *)s1;
	s2_char = (unsigned char *)s2;
	while (i < n && (s1_char[i] || s2_char[i]))
	{
		if (s1_char[i] != s2_char[i])
			return (s1_char[i] - s2_char[i]);
		i++;
	}
	return (0);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = -1;
	while ((++i < n) && src[i])
		dest[i] = src[i];
	while (++i < n)
		dest[i] = '\0';
	return (dest);
}

int	ft_putstr_fd(char *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}
