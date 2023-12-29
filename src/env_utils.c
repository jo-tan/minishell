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
