/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:26:38 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/13 20:17:54 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ismeta(char c)
{
	return (c == '|' || c == '<' || c == '<');
}

int	ft_isenvname(char c)
{
	return (ft_isalnum(c) || c == '_');
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

int	ft_count_quote_len(char  *string)
{
	int	len;

	len = 0;
	if (ft_isquote(string[len]))
	{
		len = 1;
		while (string[len] != string[0])
			len++;
		len++;
	}
	else
	{
		len = 0;
		while (string[len] && !ft_isquote(string[len]))
			len++;
	}
	return (len);
}

t_token	*ft_break_string(char *string)
{
	int		word_len;
	char	*word;
	t_token	*new;
	t_token	*head;

	head = new = NULL;
	while (*string)
	{
		word_len = ft_count_quote_len(string);
		word = malloc(word_len + 1);
		if (!word)
			return (NULL); //handle malloc failure
		ft_strlcpy(word, string, word_len + 1);
		new = ft_newtoken(word);
		if (head == NULL)
			head = new;
		else
			ft_addtoken(head, new);
		string += word_len;
	}
	return (head);
}

void	process_single(char	**word)
{
	char	*clean;
	int		len;
	int		i;
	int		j;

	i = 1;
	j = 0;
	len = ft_strlen(*word);
	clean = malloc(len - 1);
	if (!clean)
		return ;
	while (i < len - 1)
	{
		clean[j] = (*word)[i];
		j++;
		i++;
	}
	clean[j] = '\0';
	free(*word);
	*word = clean;
}

void	process_double(char	**word, t_env *env, int exit_code)
{
	char	*copy;

	process_single(word);
	copy = ft_strdup(*word);
	printf("check copy: %s\n", copy);
	expansion(word, env, exit_code);
}

void	ft_process_quote(t_token *lst, t_env *env, int	exit_code)
{
	t_token	*p;

	p = lst;
	while (p)
	{
		if ((p->word[0]) == '\'')
			process_single(&(p->word));
		if ((p->word[0]) == '\"')
			process_double(&(p->word), env, exit_code);
		p = p->next;
	}
}

char	*ft_combine(t_token *lst)
{
	char	*ret;
	char	*tmp;
	t_token	*p;

	ret = malloc(1);
	if (!ret)
		return (NULL); //handle malloc failure
	ret[0] = '\0';
	p = lst;
	while (p)
	{
		tmp = ft_strjoin(ret, p->word);
		free(ret);
		ret = tmp;
		p = p->next;
	}
	return (ret);
}

void	clear_quote(char **string, t_env *env, int exit_code)
{
	t_token	*pre;
	char *new;

	pre = ft_break_string(*string);
	ft_print_token_lst(pre);
	ft_process_quote(pre, env, exit_code);
	ft_print_token_lst(pre);
	new = ft_combine(pre);
	ft_token_free_lst(pre);
	free(*string);
	*string = new;
}

void    ft_parsing(t_mini *mini)
{
	t_token	*p;

	p = mini->token_lst;
	while (p)
	{
		if (ft_check_quote_pair(p->word) != 3)
			clear_quote(&(p->word), mini->env, mini->exit_code);
		else
			expansion(&(p->word), mini->env, mini->exit_code);
		p = p->next;
	}
}
