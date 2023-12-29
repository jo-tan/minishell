#include "minishell.h"

int	ft_get_vector_size(char **vector)
{
	int	i;

	i = 0;
	while (vector[i] != NULL)
		i++;
	return (i);
}

void	ft_unset_update(char ***msh_env, char **new_env)
{
	ft_free_char_vector(msh_env[0]);
	msh_env[0] = new_env;
}

int	ft_remove_from_env(char ***msh_env, int match_index)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = malloc(sizeof(char *) * ft_get_vector_size(msh_env[0]));
	if (!new_env)
		return (ft_error(NULL, 0, 1));
	i = 0;
	j = 0;
	while (msh_env[0][i] != NULL)
	{
		if (i != match_index)
		{
			new_env[j] = ft_strdup(msh_env[0][i]);
			if (!new_env[j])
			{
				ft_error(NULL, 0, 1);
				return (ft_free_char_vector_index(new_env, (j - 1)), 1);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (ft_unset_update(msh_env, new_env), 0);
}

int	ft_unset(char **args, char ***msh_env)
{
	int	i;
	int	m_index;

	i = 1;
	while (args[i] != NULL)
	{
		if (ft_str_contains_char(args[i], '='))
			m_index = -1;
		else
			m_index = ft_find_in_env(msh_env[0], args[i], ft_strlen(args[i]));
		if (m_index != -1)
		{
			if (ft_remove_from_env(msh_env, m_index))
				return (1);
		}
		i++;
	}
	return (0);
}
