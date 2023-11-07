/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:27:05 by jo-tan            #+#    #+#             */
/*   Updated: 2022/12/19 15:49:41 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = (int)ft_strlen(s);
	if (s[len] == (char) c)
		return ((char *)(s + len));
	while (len != -1)
	{
		if (s[len] == (char) c)
			return ((char *)(s + len));
		len--;
	}
	return (NULL);
}
