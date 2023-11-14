#include "minishell.h"

static int	ft_check_backslash(const char *line)
{
	char	*p;

	p = (char *)line;
	while (*p)
	{
		if (*p == '\\')
			return (0);
		p++;
	}
	return (1);
}

static int	ft_check_semicolon(const char *line)
{
	char	*p;

	p = (char *)line;
	while (*p)
	{
		if (*p == ';')
			return (0);
		p++;
	}
	return (1);
}

int	ft_valid_line(const char *line)
{
	if (!ft_check_backslash(line))
		return (ft_putstr_fd("Invalid input: backslash '\\' is found\n", 2), 0);
	else if (!ft_check_semicolon(line))
		return (ft_putstr_fd("Invalid input: semicolon ';' is found\n", 2), 0);
	else if (!ft_check_quote_pair(line))
		return (ft_putstr_fd("Invalid input: quote isn't closed\n", 2), 0);
	return (1);
}