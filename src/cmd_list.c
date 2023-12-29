#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_token_free_lst(cmd->tokens);
	free(cmd);
}

t_cmd	*ft_lstnew_cmd(t_token *tokens)
{
	t_cmd	*strct;

	strct = calloc(1, sizeof(*strct));
	if (!strct)
		return (NULL);
	strct->tokens = tokens;
	return (strct);
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	t_cmd	*strct;

	if (!lst)
		return (NULL);
	strct = lst;
	while (strct->next)
	{
		strct = strct->next;
	}
	return (strct);
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*strct;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		strct = ft_lstlast_cmd(*lst);
		strct->next = new;
	}
}

void	free_cmd_list(t_cmd **lst)
{
	t_cmd	*strct;

	if (!lst)
		return ;
	strct = *lst;
	while (strct)
	{
		strct = strct->next;
		free_cmd(*lst);
		*lst = strct;
	}
	*lst = NULL;
}

int ft_lstsize_cmd(t_cmd *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}