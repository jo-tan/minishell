#include "minishell.h"
t_token *ft_newtoken(char *s)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
    {
        free(s);
        return(NULL);
    }
    new->word = s;
    new->type = NONE;
    new->next = NULL;
    return (new);
}

void    ft_addtoken(t_token *lst, t_token *new)
{
    if (!new)
        return;
    if (lst == NULL)
    {
        lst = new;
        return ;
    }
    while (lst->next != NULL)
        lst = lst->next;
    lst->next = new;
}

void ft_free_token_lst(t_token *lst)
{
    while (lst)
    {
        free(lst->word);
        lst = lst->next;
    }
}

t_token *ft_tokenizer(const char  *line)
{
    int     word_len;
    char    *word;
    t_token *new = NULL;
    t_token *head = NULL;

    while (*line)
    {
        if ((*line == ' ') || (*line == '\t'))
            line++;
        else
        {
            word_len = 0;
            if (*line == 39 || *line == 34)
            {
                while (((*(line + word_len + 1)) != *line) && (*(line + word_len)) != '\0')
                    word_len++;
                word_len += 2;
            }
            else
            {
                while ((*(line + word_len)) != ' ' && (*(line + word_len)) != '\0')
                    word_len++;
            }
            word = malloc(word_len + 1);
            if (!word)
                return (NULL);
            ft_strlcpy(word, line, word_len + 1);
            printf("word: %s\n", word);
            new = ft_newtoken(word);
            if (head == NULL)
                head = new;
            else
                ft_addtoken(head, new);
            printf("word_len: %d\n", word_len);
            line += word_len;
        }
    }
    return (head);
}

t_token *ft_read_line(const char *line)
{
    t_token *token_lst;

    printf(".............\n❙input line❙ %s\n.............\n", line);
    token_lst = ft_tokenizer(line);

    ft_print_token_lst(token_lst);

    return (token_lst);
}