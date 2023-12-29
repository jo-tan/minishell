/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:25:57 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/14 17:01:01 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	global_signal = 0;

int	exit_minishell(t_mini *mini, int exit_status)
{
	if (exit_status)
		perror("minishell");
	else
		write(1, "exit\n", ft_strlen("exit\n"));
	//free everything
	free(mini->line);
	ft_token_free_lst(mini->token_lst);
	ft_free_envp(mini->env);
	rl_clear_history();
	exit (exit_status);
}

static void	parent_signal_handler(int signal)
{
	global_signal = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	parent_signal(void)
{
	// SIGINT sets $? to 130 (in child, $? will become 131)
	signal(SIGINT, &parent_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	update_exit_status(t_mini *msh, int exit_status)
{
	char	*str;

	if (msh->exit_code == exit_status)
		return ;
	msh->exit_code = exit_status;
	str = ft_itoa(exit_status);
	if (!str)
		exit_minishell(msh, -1);
	free(msh->exit_code_str);
	msh->exit_code_str = str;
}

int	input_and_parse(t_mini *mini)
{
	mini->line = readline("▼・ᴥ・▼ฅ 𐆑𐆑minishell𐆑𐆑𐰷 ");
	if (!mini->line)
		exit_minishell(mini, 0);
	if (!*(mini->line))
	{
		if (global_signal)
			mini->exit_code = 130;
		return (free(mini->line), 1);
	}
	if (ft_strlen(mini->line) > 0)
		add_history(mini->line);
	if (ft_read_line(mini) == -1)
	{
		ft_putstr_fd("minishell: Invalid Syntax\n", 2);
		return (free(mini->line), 1);
	}
	free(mini->line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("HINT: ./minishell\n", 2), 1);
	/*Initialize*/
	if (init_envp(&mini, envp) == 1)
		return (ft_putstr_fd("fail to copy environment variables.\n", 2), 1);
	//ft_print_env_list(mini.env);
	mini.exit_code = 0;
	parent_signal();
	while (1)
	{
		if (input_and_parse(&mini))
			continue ;
		//ft_print_token_lst(mini.token_lst);
		//print_cmd(mini.cmd_table);
		mini.exit_code = ft_exec(mini.cmd_table, mini.env, mini.exit_code, &mini);
		update_exit_status(&mini, mini.exit_code);
	}
	return (0);
}
