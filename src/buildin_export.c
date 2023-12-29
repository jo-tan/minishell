#include "minishell.h"

void	ft_write_export(char **msh_env, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (msh_env[i])
	{
		write(fd, "declare -x ", 11);
		j = 0;
		while (msh_env[i][j] != '=' && msh_env[i][j] != '\0' )
		{
			write(fd, &msh_env[i][j], 1);
			j++;
		}
		if (msh_env[i][j] != '\0')
		{
			write(fd, "=\"", 2);
			write(fd, &msh_env[i][(j + 1)], ft_strlen(&msh_env[i][(j + 1)]));
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		i++;
	}
}

int	ft_export_is_valid(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		write(2, "minishell: export: `", 20);
		write(2, str, ft_strlen(str));
		write(2, "\': not a valid identifier\n", 26);
		return (0);
	}
	i = 1;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			write(2, "minishell: export: `", 20);
			write(2, str, ft_strlen(str));
			write(2, "\': not a valid identifier\n", 26);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export_replace_or_add(char ***msh_env, char *str)
{
	char	*str_copy;
	int		match_index;
	int		len;

	len = 0;
	while (str[len] != '=' && str[len] != '\0')
		len++;
	match_index = ft_find_in_env(msh_env[0], str, len);
	str_copy = ft_strdup(str);
	if (!str_copy)
		return (ft_error(NULL, 0, 1));
	if (match_index >= 0)
	{
		free(msh_env[0][match_index]);
		msh_env[0][match_index] = str_copy;
		return (0);
	}
	return (ft_add_to_msh_env(msh_env, str_copy));
}

int	ft_export(char **args, char ***msh_env, int fd)
{
	int		i;
	int		error_flag;

	if (args[1] == NULL)
		return (ft_write_export(msh_env[0], fd), 0);
	i = 1;
	error_flag = 0;
	while (args[i] != NULL)
	{
		if (ft_export_is_valid(args[i]))
		{
			if (ft_export_replace_or_add(msh_env, args[i]))
				return (1);
		}
		else
			error_flag = 1;
		i++;
	}
	return (error_flag);
}
