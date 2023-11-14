#include "minishell.h"

t_cmd   *ft_newcmd(t_token *token_lst)
{
    t_cmd *new;

    new = malloc(sizeof(t_cmd));
    if (!new)
    {
        ft_token_free_lst(token_lst);
        write(1, "ft_newcmd: malloc failed.\n", ft_strlen("ft_newcmd: malloc failed.\n"));
        //exitcode?
        return ;
    }
    new->token = token_lst;
    new->next = NULL;
    return (new);
}

void    ft_addcmd(t_cmd *head, t_cmd *new)
{
    if (!new)
        return ;
    if (head == NULL)
    {
        head = new;
        return ;
    }
    while (head->next != NULL)
        head = head->next;
    head->next = new;
}

t_cmd    **ft_token_to_cmd_array(t_token *token_lst)
{
    t_token *p;
    t_cmd   **cmd_table;
    t_cmd   *current_cmd_line;

    p = token_lst;
    *cmd_table = current_cmd_line;
    cmd_line = ft_newcmd(p);

    while (p->next)
    {
        if (p->type == PIPE)
        {
            ft_addcmd(cmd_line, ft_newcmd(p->next));
            free(p->word); // get rid of the PIPE token..?
            p->next = NULL;
            p = p->next;
        }
        else
            p = p->next;
    }
    return (cmd_table);
}