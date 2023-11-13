#include "minishell.h"

t_token *ft_newtoken(char *s)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
    {
        free(s);
        return(NULL); //build a function to handle malloc error and free everything in the end
    }
    new->word = s;
    new->type = NONE;
    new->isquote = UNSET;
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
        return ; //build a function to handle malloc error and free everything in the end
    }
    while (lst->next != NULL)
        lst = lst->next;
    lst->next = new;
}

void    ft_token_free_lst(t_token *lst)
{
    while (lst)
    {
        free(lst->word);
        lst = lst->next;
    }
}
