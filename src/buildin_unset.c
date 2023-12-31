#include "minishell.h"

int	ft_get_vector_size(char **vector)
{
	int	i;

	i = 0;
	while (vector[i] != NULL)
		i++;
	return (i);
}

int	ft_remove_from_env(t_env *env, t_env *the_rm_env)
{
	t_env *pos;

	if (!env || !the_rm_env)
		return (ft_error(NULL, 0, 1));
	if (env == the_rm_env)
	{
		env = the_rm_env->next;
		free(the_rm_env->line);
		free(the_rm_env);
		return (0);
	}
	pos = env;
    while (pos != NULL && pos->next != the_rm_env)
        pos = pos->next;
    if (pos != NULL)
    {
        pos->next = the_rm_env->next;
        free(the_rm_env->line);
        free(the_rm_env);
        return (0);
    }
	return (ft_error(NULL, 0, 1));
}

int	ft_unset(char **args, t_env *env)
{
	int	i;
	t_env *the_env;

	i = 1;
	while (args[i] != NULL)
	{
		if (ft_str_contains_char(args[i], '='))
			the_env = NULL;
		else
			the_env = ft_find_in_env(env, args[i], ft_strlen(args[i]));
		if (the_env != NULL)
		{
			if (ft_remove_from_env(env, the_env))
				return (1);
		}
		i++;
	}
	return (0);
}
