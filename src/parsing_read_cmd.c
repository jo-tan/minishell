#include "minishell.h"
t_token *ft_newtoken(char *s)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
        return(NULL);
    new->word = s;
    new->type = NONE;
    new->next = NULL;
    return (new);
}

t_token *ft_lexs(const char  *line)
{
    //char *word;
    t_token *new = NULL;

    while (!*line)
    {
        if (*line == ' ' || *line == '\t')
            line++;
        else
        {
           // ft_word_into_token();
        }
    }
    //while (!*line), if space or tab line++, if word get len and create a token
    return (new);
}

t_token *ft_read_line(const char *line)
{
    t_token *token_lst;

    printf(".............\n❙input line❙ %s\n.............\n", line);
    token_lst = ft_lexs(line);

    //ft_print_token_lst(token_lst);

    return (token_lst);
}