#include "minishell.h"

int ft_check_quote_pair(const char *line)
{
    int quote;
    int inquote_len;
    char    *p;

    quote = 0;
    p = (char *)line;
    while (*p)
    {
        if (*p == '\'' || *p == '\"')
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

void    ft_update_token_isquote(t_token *lst)
{
    t_token *p;

    if (!lst)
        return ;
    p = lst;
    while (p)
    {
        if (ft_strncmp(p->word, "\'", 1) == 0 || ft_strncmp(p->word, "\"", 1) == 0)
        {
            if (ft_strncmp(p->word, "\'", 1) == 0)
                p->isquote = SINGLE;
            if (ft_strncmp(p->word, "\"", 1) == 0)
                p->isquote = DOUBLE;
        }
        p = p->next;
    }
}

void clear_quote(char **word)
{
    char    *new;

    if (!word || !*word)
        return ;
    new = malloc(ft_strlen(*word) - 1);
    if (!new)
        return ;
    ft_strlcpy(new, *word + 1, ft_strlen(*word) - 1);
    free(*word);
    *word = new;
}

void    ft_update_token_clean_quote(t_token *lst, void (clear_quote)(char **))
{
    t_token *p;

    if (!lst || !clear_quote)
        return ;
    p = lst;
    while (p)
    {
        if (p->isquote != UNSET)
            clear_quote(&p->word);
        p = p->next;
    }
}
