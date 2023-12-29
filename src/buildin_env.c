#include "minishell.h"

int	ft_env(char **args, char **msh_env, int fd)
{
	int	i;

	if (args[1] != NULL)
	{
		write(2, "env: warning: additional arguments to env are ignored\n", 54);
	}
	i = 0;
	while (msh_env[i] != NULL)
	{
		if (ft_str_contains_char(msh_env[i], '='))
		{
			write(fd, msh_env[i], ft_strlen(msh_env[i]));
			write(fd, "\n", 1);
		}
		i++;
	}
	return (0);
}
