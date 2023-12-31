#include "minishell.h"

t_env	*ft_new_env_node(char *s)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(s);
		return (NULL);
	}
	new->line = s;
	new->next = NULL;
	return (new);
}

void	ft_add_env(t_env *lst, t_env *new)
{
	if (!new)
		return ;
	if (lst == NULL)
	{
		lst = new;
		return ;
	}
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new;
}

t_env	*ft_find_in_env(t_env *env, char *target, int target_len)
{
	t_env	*p;
	int	env_len;
	int	len;

	p = env;
	while (p)
	{
		env_len = 0;
		while (p->line[env_len] != '\0' && p->line[env_len] != '=')
			env_len++;
		if (env_len > target_len)
			len = env_len;
		else
			len = target_len;
		if (ft_strncmp(&p->line[0], target, len) == 0)
			return (p);
		p = p->next;
	}
	return (NULL);
}

int	ft_add_to_msh_env(t_env *env, char *new_str)
{
	ft_add_env(env, ft_new_env_node(new_str));
	return (0);
}

size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->line != NULL)
		{
			lst_len += ft_strlen(lst->line);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char	*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	if (!(env = malloc(sizeof(char) * size_env(lst) + 1)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->line != NULL)
		{
			j = 0;
			while (lst->line[j])
			{
				env[i] = lst->line[j];
				i++;
				j++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

char	*ft_get_env(t_env *env, char *var_name)
{
	t_env 	*the_env;
	int		len;

	len = ft_strlen(var_name);
	if (len == 0)
		return (NULL);
	the_env = ft_find_in_env(env, var_name, len);
	if (!the_env)
		return (NULL);
	return (the_env->line + len + 1);
}

char	**create_env_arr(t_env *env)
{
	char *p;
	char **env_arr;

	p = env_to_str(env);
	env_arr = ft_split(p, '\n');
	free(p);
	return (env_arr);
}