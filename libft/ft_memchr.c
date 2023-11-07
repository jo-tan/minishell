/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:31:43 by jo-tan            #+#    #+#             */
/*   Updated: 2022/11/17 17:01:35 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	c2;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	c2 = (unsigned char)c;
	while (i < n)
	{
		if (*(ptr + i) == c2)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
