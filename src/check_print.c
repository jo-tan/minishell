#include "minishell.h"

void    ft_print_token_lst(t_token *token_lst)
{
    t_token *p;

    p = token_lst;
    while (p)
    {
        printf("❮%d/%s❯", p->type, p->word);
        p = p->next;
    }
    printf("\n");
}