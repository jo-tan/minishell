#include "minishell.h"

static void reprompt(int signal)
{
    (void)signal;
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
/*brief: keep reprompt and disable SIGQUIT
no return value*/
void    change_signal(void)
{
    signal(SIGINT, reprompt);
    signal(SIGQUIT, SIG_IGN);
}

static int ft_empty_str(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int main(int argc, char **argv, char **envp)
{
    char    *line;

    (void)envp;
    (void)argv;
    if (argc != 1)
        return (ft_putstr_fd("ARG_ERR: wrong argument number\nHINT: ./minishell", 2), 1);
    /*Initialize*/
    //initialize signal: to block the parent signal which may affect current terminal
    /*Clear histroy && create/build current history list*/
    while (1)
    {
        change_signal();
        line = readline("minishell:~$>");
        if (!line)
            exit(1);
        if (ft_strncmp(line, "", 1) == 0 || ft_empty_str(line))
            continue ;
        if (ft_strlen(line) > 0)
            add_history(line);
    }
    //exit(): clear everything and exit. beaware of the case 'exit | exit'. This should not work 
    return (0);
}
