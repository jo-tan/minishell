/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:02:31 by jo-tan          #+#    #+#             */
/*   Updated: 2023/11/08 18:02:34 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void reprompt(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
/*brief: keep reprompt and disable ctr+\ and ctr+Z
no return value*/
void    change_signal(void)
{
	// SIGINT sets $? to 130
	signal(SIGINT, reprompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

// includes spaces and tabs
static int ft_empty_str(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		// if (line[i] != ' ' || line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	char    *line;

	(void)envp;
	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("ARG_ERR: wrong argument number\nHINT: ./minishell\n", 2), 1);
	/*Initialize*/
	//initialize signal: to block the parent signal which may affect current terminal
	/*Clear histroy && create/build current history list*/
	while (1)
	{
		change_signal();
		line = readline("minishell:~$>");
		// When Ctrl-D : exit minishell, free everything, return exit code
		if (!line)
			exit(1);
		// if (!*line)
		// if empty string: is added into history, is not executed, does not change exit code
		if (ft_strncmp(line, "", 1) == 0 || ft_empty_str(line))
			continue ;
		if (ft_strlen(line) > 0)
			add_history(line);
	}
	//exit(): clear everything and exit. beaware of the case 'exit | exit'. This should not work 
	return (0);
}
