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
	//word after '<'. The file name, if not exit, will return error msg: "bash: hey: No such file or directory"
	HERE_DOC = 4, // word == '<<'
	// word after '<<' The specific word to end stdin/fd(n)
	FILE_OUT = 5, // word == '>'
	//word after '>' overwrite the file or create if not exist. If there is cmd before >, it will write result into the file 
	FILE_OUT_AP = 6 //word == '>>'
	//word after '>>', append the file or create if not exist.
} e_type;

/*This is smallest element of cmd line. */
typedef struct s_token
{
	char			*word;
	e_type			type;
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
	char			*line;
	int				exit_code;
} t_mini;

/*envp*/
int		init_envp(t_mini *mini, char **envp);
void	ft_free_envp(t_env *env);

/*signal*/
void	parent_signal(void);

/*check valid input*/
int 	ft_check_quote_pair(const char *line);
int		ft_valid_line(const char *line);

/*read_cmd*/
int 	ft_read_line(t_mini *mini);
t_token *ft_tokenizer(const char  *line);
int 	ft_count_word_len(const char *line);
void    ft_update_token_type(t_token *lst);

/*parsing*/
void	clear_quote(char **word, t_env *env, int exit_code);
char	*ft_combine(t_token *lst);
void    ft_parsing(t_mini *mini);

/*parsing quotes*/
int		ft_count_quote_len(char  *string);
t_token	*ft_break_string(char *string);
void	process_single(char	**word);
void	process_double(char	**word, t_env *env, int exit_code);
void	ft_process_quote(t_token *lst, t_env *env, int	exit_code);

/*parsing expansion*/
void    expansion(char **word, t_env *env, int exit_code);
void	ft_process_env(t_token *pre, t_env *env, int exit_code);
void	switch_arg_env(char	**word, t_env *env, int exit_code);
char    *get_env_value(char *word, t_env *env);
t_token	*ft_divide_arg_env(char *string);
int		ft_count_parsing_len(char *word);
int 	check_expansion_sign(char *word);

/*token list function*/
t_token *ft_newtoken(char *s);
void    ft_addtoken(t_token *lst, t_token *new);
void	ft_token_free_lst(t_token *lst);

/*Printf for checking progress*/
void    ft_print_token_lst(t_token *token_lst);
void    ft_print_env_list(t_env *env);


#endif
