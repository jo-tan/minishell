/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:25:28 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/14 15:23:51 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	NONE = 0, //defaullt
	ARG = 1, // word
	PIPE = 2, // word == pipe >> not sure if this is needed
	FILE_IN = 3, // word == '<'
	OPEN_FILE = 33, // word after '<'. The file name, if not exit, will return error msg: "bash: hey: No such file or directory"
	HERE_DOC = 4, // word == '<<'
	HD_WORD = 44, // word after '<<' The specific word to end stdin/fd(n)
	FILE_OUT = 5, // word == '>'
	EXIT_FILE = 55, // word after '>' overwrite the file or create if not exist. If there is cmd before >, it will write result into the file 
	FILE_OUT_AP = 6, //word == '>>'
	EXIT_FILE_AP = 66 //word after '>>', append the file or create if not exist.

} e_type;

typedef enum
{
	UNSET = 100,
	SINGLE = 101,
	DOUBLE = 102,
} e_isquote;


/*This is smallest element of cmd line. */
typedef struct s_token
{
	char			*word;
	e_type			type;
	e_isquote		isquote;
	struct s_token	*next;
} t_token;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
} t_env;

typedef struct	s_mini
{
	t_token			*token_lst;
	t_env			*env;
	t_env			*buildin_env;
	int				exit_code;
} t_mini;

/*signal*/
void	change_signal(void);

/*Check valid input string*/
int	ft_valid_line(onst char *line);

/*Parsing line to list of tokens*/
t_token *ft_read_line(const char *line, const char **envp);
t_token *ft_tokenizer(const char  *line);
int 	ft_count_word_len(const char *line);
void    ft_update_token_type(t_token *lst);

/*Parsing quotes*/
int 	ft_check_quote_pair(const char *line);
void    ft_update_token_isquote(t_token *lst, const char **envp);
void	clear_quote(char **word);
void    ft_update_token_clean_quote(t_token *lst, void (*clear_quote)(char **));

/*token list function*/
t_token *ft_newtoken(char *s);
void    ft_addtoken(t_token *lst, t_token *new);
void	ft_token_free_lst(t_token *lst);

/*Printf for checking progress*/
void    ft_print_token_lst(t_token *token_lst);

#endif
