/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 21:02:58 by aauthier          #+#    #+#             */
/*   Updated: 2023/12/01 16:04:57 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"

static void	free_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

static t_result	execve_fail(char **av, char *cmd_path)
{
	free_av(av);
	free(cmd_path);
	perror("pipex");
	return (ERROR);
}

t_result	child_a(int infile, t_params *params)
{
	char	**av;
	char	*cmd_path;

	av = ft_split(params->argv[2], " \t\n\v\f\r");
	close(params->pipefd[0]);
	dup2(params->pipefd[1], 1);
	close(params->pipefd[1]);
	dup2(infile, 0);
	close(infile);
	if (!av[0])
	{
		free_av(av);
		return (print_path_cmd_error("", 2));
	}
	cmd_path = find_cmd(av[0], params->env);
	if (!cmd_path)
	{
		free_av(av);
		return (ERROR);
	}
	if (execve(cmd_path, av, params->env) == -1)
		return (execve_fail(av, cmd_path));
	free_av(av);
	free(cmd_path);
	exit(0);
}

t_result	child_b(int outfile, t_params *params)
{
	char	**av;
	char	*cmd_path;

	av = ft_split(params->argv[3], " \t\n\v\f\r");
	dup2(params->pipefd[0], 0);
	close(params->pipefd[1]);
	dup2(outfile, 1);
	close(outfile);
	if (!av[0])
	{
		free(av);
		return (print_path_cmd_error("", 2));
	}
	cmd_path = find_cmd(av[0], params->env);
	if (!cmd_path)
	{
		free_av(av);
		return (ERROR);
	}
	if (execve(cmd_path, av, params->env) == -1)
		return (execve_fail(av, cmd_path));
	free_av(av);
	free(cmd_path);
	exit(0);
}
