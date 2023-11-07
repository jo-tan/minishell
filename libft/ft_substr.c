/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:15:09 by jo-tan            #+#    #+#             */
/*   Updated: 2022/12/13 22:26:31 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_malloc_emptystr(void)
{
	char	*res;

	res = malloc(1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

int	ft_fitlen(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;

	i = (unsigned int)ft_strlen(s);
	if ((i - start) < (unsigned int)len)
		return (i - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_malloc_emptystr());
	else
	{
		res = (char *)malloc((ft_fitlen(s, start, len) + 1) * sizeof(char));
		if (!res)
			return (NULL);
		while (s[start] != '\0' && i < len)
		{
			res[i] = s[start];
			i++;
			start++;
		}
		res[i] = '\0';
		return (res);
	}
}
