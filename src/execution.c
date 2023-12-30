#include "minishell.h"

int	ft_set_pipes(t_cmd **cmd_list, int nbr_cmd)
{
	int	i;
	int	pipe_ends[2];

	i = 0;
	while (i < (nbr_cmd - 1))
	{
		if (pipe(pipe_ends) == -1)
			return (ft_error(NULL, 0, 1));
		cmd_list[i + 1]->in_fd = pipe_ends[0];
		cmd_list[i]->out_fd = pipe_ends[1];
		i++;
	}
	return (0);
}

int	ft_exec_init(t_cmd **cmd_list, int old_exit)
{
	int		i;
	t_token	*t;

	i = 0;
	while (cmd_list[i] != NULL)
	{
		cmd_list[i]->in_fd = 0;
		cmd_list[i]->out_fd = 1;
		cmd_list[i]->old_exit = old_exit;
		t = cmd_list[i]->tokens;
		while (t)
		{
			t->fd = 0;
			t = t->next;
		}
		i++;
	}
	return (i);
}

void	ft_exec_msh_free(t_mini *msh)
{
	if (!msh)
		return ;
	ft_free_char_vector(msh->env_arr);
	ft_free_all(msh->cmd_table, msh->env);
}

int	ft_exec(t_cmd **cmd_list, char **env_arr, int e, t_mini *msh)
{
	int		nbr_cmd;
	int		buildin_num;

	nbr_cmd = ft_exec_init(cmd_list, e);
	if (ft_set_hdoc(cmd_list) || ft_set_pipes(cmd_list, nbr_cmd))
	{
		ft_close_all(cmd_list);
		if (global_signal)
			return (ft_free_all(cmd_list, NULL), global_signal + 128);
		return (ft_free_all(cmd_list, NULL), 1);
	}
	buildin_num = ft_is_buildin(cmd_list[0]->tokens);
	if (nbr_cmd == 1 && buildin_num)
	{
		e = ft_child(cmd_list, 0, env_arr, 1);
		if (buildin_num == B_EXIT)
		{
			ft_exec_msh_free(msh);
			exit (e);
		}
	}
	else
		e = ft_pipeline(cmd_list, nbr_cmd, env_arr, msh);
	return (ft_free_all(cmd_list, NULL), e);
}