/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:32:51 by aauthier          #+#    #+#             */
/*   Updated: 2023/12/20 19:38:11 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isbuiltin(t_token *token_list, char **envp)
{
	if (ft_strncmp("echo", token_list->word, 4) == 0)
		return (ft_echo(token_list));
	else if (ft_strncmp("cd", token_list->word, 2) == 0)
		return (ft_cd(token_list, envp));
	else if (ft_strncmp("pwd", token_list->word, 3) == 0)
		ft_pwd(token_list, envp);
	else if (ft_strncmp("export", token_list->word, 6) == 0)
		return (ft_export(token_list));
	else if (ft_strncmp("unset", token_list->word, 5) == 0)
		return (ft_unset(token_list));
	else if (ft_strncmp("env", token_list->word, 3) == 0)
		return (ft_env(token_list));
	else if (ft_strncmp("exit", token_list->word, 4) == 0)
		return (ft_exit(token_list));
	return (9); //?
}

static e_type	next_delimiter(t_token *token_list)
{
	e_type	token_type;

	while (token_list)
	{
		token_type = token_list->type;
		if (token_type == PIPE || token_type == FILE_IN
			|| token_type == HERE_DOC || token_type == FILE_OUT
			|| token_type == FILE_OUT_AP)
		{
			return (token_type);
		}
		token_list = token_list->next;
	}
	return (0);
}

int	main_exec(t_token *token_list, char **envp)
{
	int		ret;
	e_type	delimit;
	t_token	*head;

	head = token_list;
//check number of delimiter ?
//find next delimiter
	delimit = next_delimiter(head);

	if (head->type == ARG)
	{
		//word is command 
		//check for builtins
		ret = isbuiltin(head);
		if (ret != 9)
			return(ret);
		else


		head = head->next;
	}
}