#include "minishell.h"

int	init_envp(t_mini *mini, char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	i = 0;
	env = NULL;
	while (envp && envp[i])
	{
		if (!(new = malloc(sizeof(t_env))))
            return (1);

        new->line = ft_strdup(envp[i]);
        new->next = NULL;

        if (!env)
            mini->env = env = new;
        else
        {
            env->next = new;
            env = new;
        }
        i++;
	}
	return (0);
}

void	ft_free_envp(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		free(env->line);
		env = env->next;
	}
}