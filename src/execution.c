/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:38:32 by aauthier          #+#    #+#             */
/*   Updated: 2023/12/01 12:33:51 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"

t_result	check_args(int argc)
{
	if (argc < 5)
	{
		error(TOO_FEW_ARG_ERROR);
		return (ERROR);
	}
	if (argc > 5)
	{
		error(TOO_MANY_ARG_ERROR);
		return (ERROR);
	}
	return (OK);
}

void	pipex(int infile, int outfile, t_params *params)
{
	pid_t	child[2];
	int		status;

	if (pipe(params->pipefd) == -1)
		return (perror("pipe"));
	child[0] = fork();
	if (child[0] < 0)
		return (perror("Fork A :"));
	if (child[0] == 0)
		child_a(infile, params);
	else
	{
		child[1] = fork();
		if (child[1] < 0)
			return (perror("Fork B :"));
		if (child[1] == 0)
			child_b(outfile, params);
		else
		{
			close(params->pipefd[0]);
			close(params->pipefd[1]);
			waitpid(child[0], &status, 0);
			waitpid(child[1], &status, 0);
		}
	}
}

static t_result	open_files(char *infile, char *outfile, int *infd, int *outfd)
{
	int			accesscode[2];

	*infd = open(infile, O_RDONLY);
	if (*infd == -1)
		perror(infile);
	*outfd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*outfd == -1)
		perror(outfile);
	if (*infd == -1 || *outfd == -1)
		return (ERROR);
	accesscode[0] = access(infile, R_OK);
	if (accesscode[0] == -1)
		perror(infile);
	accesscode[1] = access(outfile, F_OK | W_OK);
	if (accesscode[1] == -1)
		perror(outfile);
	if ((accesscode[0] == -1) || (accesscode[1] == -1))
		return (ERROR);
	return (OK);
}

int	main_exec(int argc, char **argv, char *const env[])
{
	int			infd;
	int			outfd;
	t_params	params;

	params.argv = argv;
	params.env = env;
	if (!check_args(argc))
		return (1);
	if (open_files(argv[1], argv[4], &infd, &outfd) == ERROR)
		return (1);
	pipex(infd, outfd, &params);
	return (0);
}
