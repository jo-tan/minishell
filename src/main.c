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

int	exit_minishell(char *line, int exit_status)
{
	if (exit_status == 130) //EOF
	{
		write(1, "exit\n", ft_strlen("exit\n"));
		//free everything
		free(line);
		rl_clear_history();
	}
	return (exit_status);
}

static void	reprompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	change_signal(void)
{
	// SIGINT sets $? to 130 (in child, $? will become 131)
	signal(SIGINT, reprompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

static int	ft_empty_str(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' || line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token_lst;

	(void)envp;
	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("HINT: ./minishell\n", 2), 1);
	/*Initialize*/
	//initialize signal: to block the parent signal which may affect current terminal
	/*Clear histroy && create/build current history list*/
	while (1)
	{
		change_signal();
		line = readline("▼・ᴥ・▼ฅ 𐆑𐆑minishell𐆑𐆑𐰷 ");
		if (!line)
			return (exit_minishell(line, 130));
		// if empty string: is added into history, is not executed, does not change exit code
		if (ft_strncmp(line, "", 1) == 0 || ft_empty_str(line))
			continue ;
		token_lst = ft_read_line(line);
		ft_print_token_lst(token_lst);
	
		if (ft_strlen(line) > 0)
			add_history(line);
		free(line);
	}
	return (0);
}


// Where do you'll call the executive part ?