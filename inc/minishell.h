#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //printf
# include <readline/readline.h>//readline library for readline
# include <readline/history.h>//readline library for readline history
# include <stdlib.h> //maloc, free, getenv (get env variables)
# include <unistd.h> //write, access, exit, getcwd(get_current_directory), chdir (change working directory), unlink (delete a name and possibly the file it refers to), execve (execute program), dup, dup2, pipe, isatty, ttyname, ttyslot
# include <fcntl.h>
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <signal.h> //signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h> //stat, lstat, fstat (get file status)
# include <sys/types.h> //open, read, close, fork
# include <dirent.h> //opendir, readdir, closedir
# include <string.h> //strerror
# include <errno.h> //perror
# include <sys/ioctl.h> //ioctl (control device)
# include <termios.h> //tcsetattr, tcgetattr
# include <curses.h> //getent, tgetflag, tgetnum, tgetstr, tgoto, tputs (direct curses interface to the terminfo capability database)
# include <term.h> //with curses.h
# include "libft.h"

typedef enum
{
	NONE, //defaullt
	ARG, // word
	PIPE, // word == pipe >> not sure if this is needed
	FILE_IN, // word == '<'
	OPEN_FILE, // word after '<'. The file name, if not exit, will return error msg: "bash: hey: No such file or directory"
	HERE_DOC, // word == '<<'
	HD_WORD, // word after '<<' The specific word to end stdin/fd(n)
	FILE_OUT, // word == '>'
	EXIT_FILE, // word after '>' overwrite the file or create if not exist. If there is cmd before >, it will write result into the file 
	FILE_OUT_AP, //word == '>>'
	EXIT_FILE_AP //word after '>>', append the file or create if not exist.

} e_type;


/*This is smallest element of cmd line. */
typedef struct s_token
{
	char	*word;
	e_type	type;
	int		isquote;
	struct s_token	*next;
} t_token;

/*signal*/
void	change_signal(void);

/*Parsing line to list of tokens*/
t_token *ft_read_line(const char *line);

/*struct list*/
t_token *ft_newtoken(char *s);
void ft_free_token_lst(t_token *lst);

/*Printf for checking progress*/
void    ft_print_token_lst(t_token *token_lst);

#endif