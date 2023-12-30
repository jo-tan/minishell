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
static void	print_syntax_err(t_token *err)
{
	char	*token;
	char	*err_msg;

	token = "newline";
	err_msg = "minishell: Syntax error near unexpected token";
	if (err)
		token = err->word;
	printf("%s `%s'\n", err_msg, token);
}

// RULES :
// Pipes must be preceeded and followed by at least one Argument
// Input Redirection must be followed by an Input File
// Here Tag must be followed by a DELIMITER
// Output Redirection must be followed by an Output File
// Append Redirection must be followed by an Append File
// LOGIC :
// Check until and including NULL node
// If nothing preceeding, must be ARG or REDIR (not PIPE)
// If ARG preceeding, can be anything
// If PIPE preceeding, must be ARG or REDIR (not PIPE)
// If REDIR preceeding, must be ARG
// If end reached, previous must not be PIPE or REDIR)

int	ft_valid_syntax_order(t_token *current)
{
	t_token	*prev;

	if (current->type == PIPE)
		return (print_syntax_err(current), 0);
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
		return (print_syntax_err(current), 0);
	return (1);
}