#include "minishell.h"

int	ft_find_in_env(char **msh_env, char *target, int target_len)
{
	int	i;
	int	env_len;
	int	len;

	i = 0;
	while (msh_env[i] != NULL)
	{
		env_len = 0;
		while (msh_env[i][env_len] != '\0' && msh_env[i][env_len] != '=')
			env_len++;
		if (env_len > target_len)
			len = env_len;
		else
			len = target_len;
		if (ft_strncmp(msh_env[i], target, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_add_to_msh_env(char ***msh_env, char *new_str)
{
	int		i;
	char	**new_env;

	i = 0;
	while (msh_env[0][i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (ft_error(NULL, 0, 1), free(new_str), 1);
	i = 0;
	while (msh_env[0][i] != NULL)
	{
		new_env[i] = ft_strdup(msh_env[0][i]);
		if (!new_env[i])
		{
			ft_error(NULL, 0, 1);
			ft_free_char_vector_index(msh_env[0], (i - 1));
			return (free(new_env), free(new_str), 1);
		}
		i++;
	}
	new_env[i] = new_str;
	new_env[i + 1] = NULL;
	ft_free_char_vector(msh_env[0]);
	return (msh_env[0] = new_env, 0);
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

char	*ft_get_env(char **msh_env, char *var_name)
{
	int		i;
	int		len;

	len = ft_strlen(var_name);
	if (len == 0)
		return (NULL);
	i = ft_find_in_env(msh_env, var_name, len);
	if (i == -1)
		return (NULL);
	return (&msh_env[i][len + 1]);
}

char	**create_env_arr(t_env *env, t_mini *mini)
{
	char *p;

	p = env_to_str(env);
	mini->env_arr = ft_split(p, '\n');
	free(p);
	if (!mini->env_arr)
	{
		ft_putstr_fd("Malloc: fail to create env_arr for execv.\n", 2);
		mini->exit_code = 1;
	}
	return (mini->env_arr);
}