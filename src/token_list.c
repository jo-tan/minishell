/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:26:12 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/13 18:40:15 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_newtoken(char *s)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(s);
		return (NULL);
	}
	new->word = s;
	new->type = NONE;
	new->next = NULL;
	return (new);
}

void	ft_addtoken(t_token *lst, t_token *new)
{
	if (!new)
		return ;
	if (lst == NULL)
	{
		lst = new;
		return ;
	}
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new;
}

void	ft_token_free_lst(t_token *lst)
{
	while (lst)
	{
		free(lst->word);
		lst = lst->next;
	}
}
