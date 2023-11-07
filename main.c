#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *line;
    if (argc != 1)
        return (ft_putstr_fd("ARF_ERR: Should be 1 argument.\n Hint: ./minishell"), 2), 1);
    /*Initialize*/
    //initialize signal: to block the parent signal which may affect current terminal
    /*Clear histroy && create/build current history list*/
    while (1)
    {    
        line = readline("minishell:~$");
        if (!line)
            exit(1);
        if (ft_strlen(line) > 0)
            add_history(line);
    }
    //exit(): clear everything and exit. beaware of the case 'exit | exit'. This should not work 

    return (0);
}