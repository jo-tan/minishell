/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:32:51 by aauthier          #+#    #+#             */
/*   Updated: 2023/12/19 17:17:49 by aauthier         ###   ########.fr       */
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

int	main_exec(t_token *token_list, char **envp)
{
	int	ret;

	if (token_list->type == ARG)
	{
		//word is command 
		//check for builtins
		ret = isbuiltin(token_list);
		if (ret != 9)
			return(ret);
		else
			
	}
}