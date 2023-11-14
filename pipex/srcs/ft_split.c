/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:24:18 by aauthier          #+#    #+#             */
/*   Updated: 2022/01/30 06:04:02 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_is_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static char	ft_wsize(char *str, char *charset, int pos)
{
	int	i;

	i = 0;
	while (str[pos])
	{
		if (!ft_is_charset(str[pos], charset))
			i++;
		pos++;
	}
	return (i);
}

static void	ft_splitu(char *str, char *to_find, char **res)
{
	int	i[3];

	i[0] = -1;
	i[1] = 0;
	i[2] = 0;
	while (str[++i[0]])
	{
		if (!ft_is_charset(str[i[0]], to_find))
		{
			if (i[2] == 0)
			{
				res[i[1]] = malloc(sizeof(char) * (ft_wsize(str, to_find, i[0])
							+ 1));
				if (!res[i[1]])
					return ;
			}
			res[i[1]][i[2]] = str[i[0]];
			res[i[1]][++i[2]] = '\0';
		}
		if (ft_is_charset(str[i[0]], to_find) && i[2] > 0)
		{
			i[2] = 0;
			i[1]++;
		}
	}
}

static int	ft_wordcount(char *str, char *charset)
{
	int	i;
	int	wcount;
	int	word;

	i = -1;
	wcount = 0;
	word = 0;
	while (str[++i])
	{
		if (ft_is_charset(str[i], charset))
			word = 0;
		else if (word == 0)
		{
			word = 1;
			wcount++;
		}
	}
	return (wcount);
}

char	**ft_split(char *str, char *charset)
{
	char	**result;

	if (!(str))
		return (NULL);
	result = malloc(sizeof(char *) * (ft_wordcount(str, charset) + 1));
	if (!result)
		return (NULL);
	ft_splitu(str, charset, result);
	result[ft_wordcount(str, charset)] = NULL;
	return (result);
}
