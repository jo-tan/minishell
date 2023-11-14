/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 00:13:26 by aauthier          #+#    #+#             */
/*   Updated: 2022/02/01 22:52:29 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "pipex.h"

char	*find_var_path(char *const env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH", env[i], 4))
			return (env[i]);
		i++;
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PWD", env[i], 3))
			return (env[i]);
		i++;
	}
	return (NULL);
}

static char	*search_cmd(t_var path, int *errcode, char *cmd)
{
	path.var_path = ft_strchr(path.var_path, '=') + 1;
	while (path.var_path != NULL && *(path.var_path) != '\0')
	{
		path.var_temp = ft_strchr(path.var_path, ':');
		if (path.var_temp == NULL)
			path.len = ft_strlen(path.var_path);
		else
			path.len = path.var_temp - path.var_path;
		path.cmd_path = ft_strnjoin_wsep(cmd, path.var_path, path.len, "/");
		if (path.cmd_path == NULL)
			return (NULL);
		if (access_cmd(errcode, path.cmd_path) != NULL)
			return (path.cmd_path);
		free(path.cmd_path);
		if (path.var_temp != NULL)
			path.var_path = path.var_temp + 1;
		else
			break ;
	}
	return (NULL);
}

char	*access_cmd(int *errcode, char *cmd_path)
{
	if (access(cmd_path, F_OK | R_OK | X_OK) == 0)
		return (cmd_path);
	else if (errno == EACCES || *errcode == EACCES)
		*errcode = EACCES;
	else
		*errcode = errno;
	return (NULL);
}

t_result	print_path_cmd_error(char *cmd, int errcode)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (errcode == 2)
		ft_putstr_fd(": Command not found\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errcode), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (ERROR);
}

char	*find_cmd(char *cmd, char *const env[])
{
	int		errcode;
	t_var	path;

	errcode = 0;
	path.var_path = find_var_path(env);
	if (path.var_path == NULL)
		return (NULL);
	path.var_path = ft_strjoin(path.var_path, ":/:./");
	path.cmd_path = search_cmd(path, &errcode, cmd);
	free(path.var_path);
	if (path.cmd_path)
		return (path.cmd_path);
	print_path_cmd_error(cmd, errcode);
	return (NULL);
}
