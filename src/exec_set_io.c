#include "minishell.h"

int	ft_file(t_cmd **cmd_list, int i, char *filename, enum e_type type)
{
	int	fd;

	fd = 0;
	if (type == FILE_IN)
		fd = open(filename, O_RDONLY);
	if (type == FILE_OUT)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (type == FILE_OUT_AP)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (fd < 0)
		return (ft_error(filename, 0, 1));
	if (type == FILE_OUT || type == FILE_OUT_AP)
	{
		if (cmd_list[i]->out_fd != 1)
			close(cmd_list[i]->out_fd);
		cmd_list[i]->out_fd = fd;
	}
	if (type == FILE_IN)
	{
		if (cmd_list[i]->in_fd != 0)
			close(cmd_list[i]->in_fd);
		cmd_list[i]->in_fd = fd;
	}
	return (0);
}

int	ft_set_io(t_cmd **cmd_list, int i, int single_flag)
{
	t_token	*t;
	int		exit_status;

	t = cmd_list[i]->tokens;
	exit_status = 0;
	while (t != NULL && exit_status == 0)
	{
		if (t->type == HERE_DOC && find_space(t->word))
		 	return (ft_ambig(t->word), 1);
		if (t->type == FILE_IN || t->type == FILE_OUT || t->type == FILE_OUT_AP)
			exit_status = ft_file(cmd_list, i, t->word, t->type);
		t = t->next;
	}
	if (exit_status == 0)
		ft_dup(cmd_list, i, single_flag);
	return (exit_status);
}

int	ft_heredoc(char *limitor, enum e_type type, int old_exit, t_env *msh_env)
{
	int		pipe_ends[2];
	char	*str;
	size_t	len;

	(void)old_exit;
	(void)msh_env;
	(void)type;
	if (pipe(pipe_ends))
		return (ft_error(NULL, 0, 0));
	len = ft_strlen(limitor);
	str = readline("> ");
	if (global_signal)
		return (close(pipe_ends[0]), close(pipe_ends[1]), 0);
	while (str && !(len == ft_strlen(str) && !ft_strncmp(limitor, str, len)))
	{
		if (ft_hdoc_write(str, pipe_ends) == 0)
			str = readline("> ");
		else if (global_signal || !str)
			return (close(pipe_ends[0]), close(pipe_ends[1]), 0);
	}
	if (!str)
		return (ft_hdoc_sig(limitor), close(pipe_ends[1]), pipe_ends[0]);
	return (free(str), close(pipe_ends[1]), pipe_ends[0]);
}

int	ft_set_hdoc(t_cmd **cmd_list, int e, t_env *msh_env)
{
	int		i;
	t_token	*token;

	i = 0;
	while (cmd_list[i])
	{
		token = cmd_list[i]->tokens;
		while (token)
		{
			if (token->type == HERE_DOC)
			{
				token->fd = ft_heredoc(token->word, token->type, e, msh_env);
				if (token->fd == 0)
					return (1);
			}
			token = token->next;
		}
		i++;
	}
	return (0);
}
