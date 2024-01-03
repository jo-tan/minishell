/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:25:57 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/03 10:35:26 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	int		exit_status;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("HINT: ./minishell\n", 2), 1);
	mini = mini_init(envp);
	parent_signal();
	while (1)
	{
		g_signal = 0;
		if (input_and_parse(mini))
			continue ;
		exit_status = ft_exec
			(mini->cmd_table, mini->env, mini->exit_code, mini);
		update_exit_status(mini, exit_status);
	}
	return (0);
}
