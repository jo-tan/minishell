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

int	ft_check_quote_pair(const char *string)
{
	int		quote;
	int		inquote_len;
	int		quote_type;
	char	*p;

	quote = 0;
	quote_type = 3;
	p = (char *)string;
	while (*p)
	{
		if (ft_isquote(*p))
		{
			inquote_len = 1;
			quote = 1;
			if (*p == '\'')
				quote_type = 1;
			else
				quote_type = 2;
			while ((*(p + inquote_len)) != '\0')
			{
				if ((*(p + inquote_len)) == *p)
				{
					quote = 0;
					p += inquote_len;
					break ;
				}
				inquote_len++;
			}
			if (quote != 0)
				return (0);
		}
		p++;
	}
	return (quote_type);
}

int	ft_valid_line(const char *line)
{
	if (!ft_check_backslash(line))
		return (ft_putstr_fd("Invalid Syntax: backslash '\\' is found\n", 2), 0);
	if (!ft_check_semicolon(line))
		return (ft_putstr_fd("Invalid Syntax: semicolon ';' is found\n", 2), 0);
	if (!ft_check_quote_pair(line))
		return (ft_putstr_fd("Invalid Syntax: quote isn't closed\n", 2), 0);
	return (1);
}

/*Rule:
If token type is not ARG, it should follow with at least one ARG after.
The last token cannot be PIPE or redirection*/

int	ft_valid_syntax_order(t_token *current)
{
	t_token	*prev;

	if (current->type == PIPE)
		return (0);
	while (current)
	{
		prev = current;
		current = current->next;
		if (!current)
			break ;
		if (prev->type == PIPE && current->type == PIPE)
			break ;
		if (prev->type > PIPE)
		{
			if (current->type != ARG)
				break ;
		}
	}
	if (prev->type > ARG)
		return (0);
	return (1);
}