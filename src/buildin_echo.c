#include "minishell.h"

int	ft_echo_is_flag(char *str)
{
	int	i;

	if ((ft_strlen(str) < 2) || (ft_strncmp(str, "-n", 2) != 0))
		return (0);
	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args, int fd)
{
	int	option_flag;
	int	i;

	if (args[1] == NULL)
	{
		write(fd, "\n", 1);
		return (0);
	}
	option_flag = 0;
	i = 1;
	while (ft_echo_is_flag(args[i]))
	{
		option_flag = 1;
		i++;
	}
	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(fd, " ", 1);
	}
	if (option_flag == 0)
		write(fd, "\n", 1);
	return (0);
}
