#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    if (argc != 1)
        return (ft_putstr_fd("ARF_ERR: Should be 1 argument.\n Hint: ./minishell"), 2), 1);
    /*Initiate*/
    //signal
    //token
    while (1)
    {
        /*Clear histroy*/
        //ft_build_histroy_list();
        /*While nothing is input, continue the prompt as loop*/
    }
    //ft_exit() beaware of the case 'exit | exit'. This should not work 

    return (0);
}