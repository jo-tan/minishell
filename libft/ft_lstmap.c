/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 04:21:56 by jo-tan            #+#    #+#             */
/*   Updated: 2022/12/15 12:19:08 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;
	t_list	*last_mapped;
	void	*mapped_element;

	if (!lst || !f || !del)
		return (NULL);
	mapped = ft_lstnew(NULL);
	last_mapped = mapped;
	while (lst)
	{
		mapped_element = f(lst->content);
		if (mapped_element != NULL)
		{
			last_mapped->next = ft_lstnew(mapped_element);
			if (last_mapped->next == NULL)
				del(mapped_element);
			else
				last_mapped = last_mapped->next;
		}
		lst = lst->next;
	}
	last_mapped = mapped;
	mapped = mapped->next;
	ft_lstdelone(last_mapped, del);
	return (mapped);
}
