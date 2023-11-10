#include "minishell.h"

void    ft_print_token_lst(t_token *token_lst)
{
    t_token *p;
    char    *type;

    p = token_lst;
    while (p)
    {
        if (p->type == NONE)
            type = "NONE";

        else if (p->type == ARG)
            type = "ARG";

        else if (p->type == PIPE)
            type = "PIPE";

        else if (p->type == FILE_IN)
            type = "FILE_IN";

        else if (p->type == OPEN_FILE)
            type = "OPEN_FILE";

        else if (p->type == HERE_DOC)
            type = "HERE_DOC";

        else if (p->type == HD_WORD)
            type = "HD_WORD";

        else if (p->type == FILE_OUT)
            type = "FILE_OUT";

        else if (p->type == EXIT_FILE)
            type = "EXIT_FILE";

        else if (p->type == EXIT_FILE)
            type = "EXIT_FILE";

        else if (p->type == EXIT_FILE_AP)
            type = "EXIT_FILE_AP";

        printf("❮%s/%s❯   ", type, p->word);
        p = p->next;
    }
    printf("\n");
}