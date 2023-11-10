#include "minishell.h"

void    ft_print_token_lst(t_token *token_lst)
{
    while (token_lst)
    {
        printf("❮%d/%s❯", token_lst->type, token_lst->word);
        token_lst = token_lst->next;
    }
    printf("\n");
}