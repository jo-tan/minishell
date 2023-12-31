#include "minishell.h"

int	ft_env(char **args, t_env *env, int fd)
{
	t_env *p;

	p = env;
	if (args[1] != NULL)
		write(2, "env: warning: additional arguments to env are ignored\n", 54);
	while (p)
	{
		if (ft_str_contains_char(p->line, '='))
		{
			write(fd, p->line, ft_strlen(p->line));
			write(fd, "\n", 1);
		}
		p = p->next;
	}
	return (0);
}
