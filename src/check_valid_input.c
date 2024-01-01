/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 10:07:06 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 12:16:48 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_backslash(const char *line)
{
	char	*p;

	p = (char *)line;
	while (*p)
	{
		if (*p == '\\')
			return (0);
		p++;
	}
	return (1);
}

static int	ft_check_semicolon(const char *line)
{
	char	*p;

	p = (char *)line;
	while (*p)
	{
		if (*p == ';')
			return (0);
		p++;
	}
	return (1);
}

char	*check_quote_ext(char *p, int *quote, int *quote_type)
{
	int	inquote_len;

	inquote_len = 1;
	if (ft_isquote(*p))
	{
		*quote = 1;
		if (*p == '\'')
			*quote_type = 1;
		else
			*quote_type = 2;
		while ((*(p + inquote_len)) != '\0')
		{
			if ((*(p + inquote_len)) == *p)
			{
				*quote = 0;
				p += inquote_len;
				break ;
			}
			inquote_len++;
		}
		if (*quote != 0)
			return (p);
	}
	return (p + 1);
}

int	ft_check_quote_pair(const char *string)
{
	int		quote;
	int		quote_type;
	char	*p;

	quote = 0;
	quote_type = 3;
	p = (char *)string;
	while (*p)
	{
		p = check_quote_ext(p, &quote, &quote_type);
	}
	return (quote_type);
}

int	ft_valid_line(const char *line)
{
	if (!ft_check_backslash(line))
		return (ft_putstr_fd("Invalid Syntax: backslash '\\' is found\n", 2), 0);
	if (!ft_check_semicolon(line))
		return (ft_putstr_fd("Invalid Syntax: semicolon ';' is found\n", 2), 0);
	if (!ft_check_quote_pair(line))
		return (ft_putstr_fd("Invalid Syntax: quote isn't closed\n", 2), 0);
	return (1);
}
