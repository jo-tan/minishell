/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:07:50 by aauthier          #+#    #+#             */
/*   Updated: 2023/12/19 12:32:38 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Dummy commands to silence errors

int	ft_echo(char **list_args)
{
	return(0);
}

int	ft_cd(char **path, char **envp)
{
	return(0);
}

int	ft_pwd(char **token_list, char **envp)
{
	return(0);
}

int	ft_export(t_token *token_list)
{
	return(0);
}

int	ft_unset(t_token *token_list)
{
	return(0);
}

int	ft_env(t_token *token_list, char **envp)
{
	return(0);
}

int	ft_exit(t_token *token_list)
{
	return(0);
}
