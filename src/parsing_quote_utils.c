/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:26:38 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/13 20:17:54 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote_pair(const char *line)
{
	int		quote;
	int		inquote_len;
	int		quote_type;
	char	*p;

	quote = 0;
	quote_type = 3;
	p = (char *)line;
	while (*p)
	{
		if (ft_isquote(*p))
		{
			inquote_len = 1;
			quote = 1;
			if (*p == '\'')
				quote_type = 1;
			else
				quote_type = 2;
			while ((*(p + inquote_len)) != '\0')
			{
				if ((*(p + inquote_len)) == *p)
				{
					quote = 0;
					p += inquote_len;
					break ;
				}
				inquote_len++;
			}
			if (quote != 0)
				return (0);
		}
		p++;
	}
	return (quote_type);
}

void	ft_update_token_isquote(t_token *lst)
{
	t_token	*p;

	if (!lst)
		return ;
	p = lst;
	while (p)
	{
		if (ft_check_quote_pair(p->word) == 1)
			p->isquote = SINGLE;
		if (ft_check_quote_pair(p->word) == 2)
			p->isquote = DOUBLE;
        if (ft_check_quote_pair(p->word) == 3)
            p->isquote = UNSET;
		p = p->next;
	}
}

void	clear_quote(char **word)
{
	(void) word;
	printf("hello! function clear_quote is in progress :P \n");
}

void	ft_update_token_clean_quote(t_token *lst, void (clear_quote)(char **))
{
	t_token	*p;

	if (!lst || !clear_quote)
		return ;
	p = lst;
	while (p)
	{
		if (p->isquote != UNSET)
			clear_quote(&p->word);
		p = p->next;
	}
}
