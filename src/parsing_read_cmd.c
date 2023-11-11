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

int ft_check_quote_pair(const char *line)
{
    int quote;
    int inquote_len;
    char    *p;

    quote = 0;
    p = (char *)line;
    while (*p)
    {
        if (*p == 39 || *p == 34)
        {
            inquote_len = 1;
            quote = 1;
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
    return (1);
}

int ft_count_word_len(const char *line)
{
    int len;
    int inquote;

    len = 0;
    if (*line == '|' || *line == '<' || *line == '>')
    {
        if ((*line == '<' || *line == '>') && (*(line + 1)) == *line)
            return (2);
        return(1);
    }
    while (*(line + len))
    {
        if ((*(line + len)) == 39 || (*(line + len)) == 34)
        {
            inquote = 1;
            while ((*(line + len + inquote)) != (*(line + len)))
            {
                inquote++;
            }
            len += inquote;
            len ++;
            break;
        }
        if ((*(line + len)) == '|' || (*(line + len)) == '<' || (*(line + len)) == '>' || (*(line + len)) == ' ' || (*(line + len)) == '\t')
            break ;
        len++;
    }
    return (len);
}

// fd" sdf" should be fd" sdf"; not [fd"] [sdf"]
t_token *ft_tokenizer(const char  *line)
{
    int     word_len;
    char    *word;
    t_token *new = NULL;
    t_token *head = NULL;

    if (!ft_check_quote_pair(line))
        return (ft_putstr_fd("ERR: quote isn't closed. Out of project scope\n", 2), NULL);
    while (*line)
    {
        if ((*line == ' ') || (*line == '\t'))
            line++;
        else
        {
            word_len = ft_count_word_len(line);
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
            write(1, "\n", 1);
            line += word_len;
        }
    }
    return (head);
}

void    ft_update_token_type(t_token *lst)
{
    t_token *p;

    p = lst;
    while (p)
    {
        if (p->type == NONE)
        {
            if (ft_strncmp(p->word, "|", ft_strlen(p->word)) == 0)
                p->type = PIPE;
            else if (ft_strncmp(p->word, "<", ft_strlen(p->word)) == 0)
            {
                p->type = FILE_IN;
                if (p->next != NULL)
                    p->next->type = OPEN_FILE;
            }
            else if (ft_strncmp(p->word, "<<", ft_strlen(p->word)) == 0)
            {
                p->type = HERE_DOC;
                if (p->next != NULL)
                    p->next->type = HD_WORD;
            }
            else if (ft_strncmp(p->word, ">", ft_strlen(p->word)) == 0)
            {
                p->type = FILE_OUT;
                if (p->next != NULL)
                    p->next->type = EXIT_FILE;
            }
            else if (ft_strncmp(p->word, ">>", ft_strlen(p->word)) == 0)
            {
                p->type = FILE_OUT_AP;
                if (p->next != NULL)
                    p->next->type = EXIT_FILE_AP;
            }
            else
                p->type = ARG;
        }
        p = p->next;
    }
}

t_token *ft_read_line(const char *line)
{
    t_token *token_lst;

    printf(".............\n❙input line❙ %s\n.............\n", line);
    token_lst = ft_tokenizer(line);
    ft_update_token_type(token_lst);

    return (token_lst);
}