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
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
/*brief: keep reprompt and disable ctr+\ and ctr+Z
no return value*/
void    change_signal(void)
{
	// SIGINT sets $? to 130 (in child, $? will become 131)
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
		if (line[i] != ' ' || line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	char    *line;
	t_token	*token_lst;

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
		line = readline("▼・ᴥ・▼ฅ 𐆑𐆑minishell𐆑𐆑𐰷 ");
		// When Ctrl-D : exit minishell, free everything, return exit code
		//ft_exit(): clear everything and exit. beaware of the case 'exit | exit'. This should not work
		if (!line)
			exit(1);
		// if (!*line) EOF, fre everthing and exit
		// if empty string: is added into history, is not executed, does not change exit code
		if (ft_strncmp(line, "", 1) == 0 || ft_empty_str(line))
			continue ;

		token_lst = ft_read_line(line);
		ft_print_token_lst(token_lst);
		ft_token_free_lst(token_lst);
		
		if (ft_strlen(line) > 0)
			add_history(line);
	}	 
	return (0);
}
