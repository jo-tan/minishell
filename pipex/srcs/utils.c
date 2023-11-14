/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:59:00 by aauthier          #+#    #+#             */
/*   Updated: 2022/01/10 19:34:55 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	pos;

	i = 0;
	pos = ft_strlen(dest);
	while (src[i])
	{
		dest[pos] = src[i];
		pos++;
		i++;
	}
	dest[pos] = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size < dst_len)
		dst_len = size;
	if (size == dst_len)
		return (src_len + size);
	if (src_len < size - dst_len)
		ft_memcpy(dst + dst_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, src, size - dst_len - 1);
		dst[size - 1] = '\0';
	}
	return (dst_len + src_len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst_char;
	unsigned char	*src_char;

	i = 0;
	dst_char = (unsigned char *)dest;
	src_char = (unsigned char *)src;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (i < n)
	{
		dst_char[i] = src_char[i];
		i++;
	}
	return (dst_char);
}
