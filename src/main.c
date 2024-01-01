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

// mini->line is freed after each readline before execution
// mini->cmd_table is freed in execution
void	free_mini(t_mini **mini)
{
	ft_free_envp((*mini)->env);
	free((*mini)->exit_code_str);
	free(*mini);
	*mini = NULL;
}

int	exit_minishell(t_mini **mini, int exit_code)
{
	if (exit_code)
		perror("");
	else
		write(1, "exit\n", 5);
	free_mini(mini);
	rl_clear_history();
	if (exit_code)
		printf("memory allocation failure");
	exit (exit_code);
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
	signal(SIGINT, &parent_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	update_exit_status(t_mini *mini, int exit_status)
{
	char	*str;

	if (mini->exit_code == exit_status)
		return ;
	mini->exit_code = exit_status;
	str = ft_itoa(exit_status);
	if (!str)
		exit_minishell(&mini, -1);
	if (mini->exit_code_str != NULL)
		free(mini->exit_code_str);
	mini->exit_code_str = str;
}

int	input_and_parse(t_mini *mini)
{
	mini->line = readline("▼・ᴥ・▼ฅ 𐆑𐆑minishell𐆑𐆑𐰷 ");
	if (!mini->line)
		exit_minishell(&mini, 0);
	if (!*(mini->line))
	{
		if (global_signal)
			mini->exit_code = 130;
		return (free(mini->line), 1);
	}
	if (ft_strlen(mini->line) > 0)
		add_history(mini->line);
	if (ft_read_line(mini) == -1)
		return (free(mini->line), 1);
	free(mini->line);
	return (0);
}

t_mini	*mini_init(char **envp)
{
	t_mini	*mini;

	mini = malloc(sizeof(*mini));
	if (!mini)
		return (perror("mini_init (mini)"), NULL);
	if (init_envp(mini, envp) == 1)
		return (perror("mini_init (mini_env)"), free(mini), NULL);
	mini->exit_code = 0;
	mini->exit_code_str = ft_strdup("0");
	if (!mini->exit_code_str)
		return (perror("mini_init (mini_exit)"), free_mini(&mini), NULL);
	return (mini);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	int		exit_status;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("HINT: ./minishell\n", 2), 1);
	/*Initialize*/
	mini = mini_init(envp);
	parent_signal();
	while (1)
	{
		if (input_and_parse(mini))
			continue ;
		//print_cmd(mini->cmd_table);
		exit_status = ft_exec(mini->cmd_table, mini->env, mini->exit_code, mini);
		update_exit_status(mini, exit_status);
	}
	return (0);
}
