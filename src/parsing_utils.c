#include "minishell.h"

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (ft_isspace(*str))
		++str;
	return (str);
}

int	end_of_cmd(int c)
{
	return (c == 0 || c == '#');
}

static int	ft_count_word_len_second(const char *line)
{
	int	len;

	len = 0;
	while (*(line + len))
	{
		if (ft_isspace(*(line + len)))
			break ;
		len++;
	}
	return (len);
}

static t_token	*process_token(const char *line, int *word_len)
{
	char	*word;

	*word_len = ft_count_word_len_second(line);
	word = malloc(*word_len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, line, *word_len + 1);
	return (ft_newtoken(word));
}

t_token *second_tokenizer(const char *word)
{
	t_token	*head;
	t_token	*new;
	int		word_len;

	head = NULL;
	new = NULL;
	word_len = 0;
	while (*word)
	{
		if (ft_isspace(*word))
			word++;
		else
		{
			new = process_token(word, &word_len);
			if (!new)
				return (NULL);
			if (head == NULL)
				head = new;
			else
				ft_addtoken(head, new);
			word += word_len;
		}
	}
	return (head);
}

t_token *ft_re_tokenize(t_token *token_lst)
{
	t_token *head = token_lst;
    t_token *p = head;
    t_token *prev = NULL;
    t_token *add = NULL;

	if (!token_lst)
		return (NULL);
    while (p)
    {
        if (find_space(p->word))
        {
            add = second_tokenizer(p->word);
            if (!add)
                return NULL;
            if (prev == NULL)
                head = add;
            else
                prev->next = add;
            while (add->next != NULL)
                add = add->next;
            add->next = p->next;
            free(p->word);
            free(p);
            p = add;
        }
        prev = p;
        p = p->next;
    }
	return (head);
}