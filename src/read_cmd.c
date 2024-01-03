/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:26:48 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/02 16:05:59 by aauthier         ###   ########.fr       */
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

static t_token	*process_token(const char *line, int *word_len)
{
	char	*word;

	*word_len = ft_count_word_len(line);
	word = malloc(*word_len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, line, *word_len + 1);
	return (ft_newtoken(word));
}

t_token	*ft_tokenizer(const char *line)
{
	t_token	*new;
	t_token	*head;
	int		word_len;

	head = NULL;
	new = NULL;
	word_len = 0;
	while (*line)
	{
		if (ft_isspace(*line))
			line++;
		else
		{
			new = process_token(line, &word_len);
			if (!new)
				return (NULL);
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
			{
				if (find_quote(p->next->word))
					p->type = DELIMITER_Q;
				else
					p->type = DELIMITER;
			}
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

//READ_LINE:
//check the input
//tokenized words with space or meta characters
//check syntax
//update token->type
//parse quote expansion
//retokenized for string with space
//form token into cmd list for execution
int	ft_read_line(t_mini *mini)
{
	char	*line;

	line = skip_spaces(mini->line);
	if (end_of_cmd(*line) == 2)
		return (update_exit_status(mini, 1), 1);
	if (end_of_cmd(*line) == 1)
		return (update_exit_status(mini, 0), 1);
	if (!ft_valid_line(mini->line))
		return (update_exit_status(mini, 2), 2);
	expansion(&mini->line, mini->env, mini->exit_code);
	mini->token_lst = ft_tokenizer(mini->line);
	ft_update_token_type(mini->token_lst);
	if (!ft_valid_syntax_order(mini->token_lst))
		return (ft_token_free_lst(mini->token_lst),
			update_exit_status(mini, 2), 2);
	ft_parsing(mini, mini->token_lst);
	mini->cmd_table = create_cmd_arr(mini->token_lst);
	return (0);
}
