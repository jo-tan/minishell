/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:26:48 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/01 09:59:18 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_word_len(const char *line)
{
	int	len;
	int	inquote;

	len = 0;
	if (ft_ismeta(*line))
	{
		if ((*line == '<' || *line == '>') && (*(line + 1)) == *line)
			return (2);
		return (1);
	}
	while (*(line + len))
	{
		if (ft_isquote(*(line + len)))
		{
			inquote = 1;
			while ((*(line + len + inquote)) != (*(line + len)))
				inquote++;
			len += inquote;
		}
		if (ft_ismeta(*(line + len)) || ft_isspace(*(line + len)))
			break ;
		len++;
	}
	return (len);
}

t_token	*ft_tokenizer(const char *line)
{
	int		word_len;
	char	*word;
	t_token	*new;
	t_token	*head;

	head = NULL;
	new = NULL;
	while (*line)
	{
		if (ft_isspace(*line))
			line++;
		else
		{
			word_len = ft_count_word_len(line);
			word = malloc(word_len + 1);
			if (!word)
				return (NULL);
			ft_strlcpy(word, line, word_len + 1);
			new = ft_newtoken(word);
			if (head == NULL)
				head = new;
			else
				ft_addtoken(head, new);
			line += word_len;
		}
	}
	return (head);
}

void	ft_update_token_type(t_token *lst)
{
	t_token	*p;

	if (!lst)
		return ;
	p = lst;
	while (p)
	{
		if (p->type == NONE)
		{
			if (ft_strncmp(p->word, "|", ft_strlen(p->word)) == 0)
				p->type = PIPE;
			else if (ft_strncmp(p->word, "<", ft_strlen(p->word)) == 0)
				p->type = FILE_IN;
			else if (ft_strncmp(p->word, "<<", ft_strlen(p->word)) == 0)
				p->type = HERE_DOC;
			else if (ft_strncmp(p->word, ">", ft_strlen(p->word)) == 0)
				p->type = FILE_OUT;
			else if (ft_strncmp(p->word, ">>", ft_strlen(p->word)) == 0)
				p->type = FILE_OUT_AP;
			else
				p->type = ARG;
		}
		p = p->next;
	}
}

int	ft_read_line(t_mini *mini)
{
	if (!ft_valid_line(mini->line))
		return (-1);
	mini->token_lst = ft_tokenizer(mini->line);
	ft_update_token_type(mini->token_lst);
	if (!ft_valid_syntax_order(mini->token_lst))
		return (-1);
	ft_parsing(mini, mini->token_lst);
	mini->cmd_table = create_cmd_arr(mini->token_lst);
	return (0);
}
