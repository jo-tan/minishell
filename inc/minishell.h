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
# include <limits.h>
# include "libft.h"

extern int	global_signal;

# define B_ECHO 1
# define B_CD 2
# define B_PWD 3
# define B_EXPORT 4
# define B_UNSET 5
# define B_ENV 6
# define B_EXIT 7

enum e_type
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
};

/*This is smallest element of cmd line. */
typedef struct s_token
{
	char			*word;
	enum e_type		type;
	int				fd;
	struct s_token	*next;
} t_token;

typedef struct s_cmd
{
	int				in_fd;
	int				out_fd;
	int				old_exit;
	struct s_token	*tokens;
	struct s_cmd	*next;
}					t_cmd;

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
	char			*exit_code_str;
	t_cmd			**cmd_table;
} t_mini;

/*envp*/
int		init_envp(t_mini *mini, char **envp);
void	ft_free_envp(t_env *env);

/*signal*/
void	parent_signal(void);

/*check valid input*/
int 	ft_check_quote_pair(const char *line);
int		ft_valid_line(const char *line);
int		ft_valid_syntax_order(t_token *token_lst);

/*read_cmd*/
int 	ft_read_line(t_mini *mini);
t_token *ft_tokenizer(const char  *line);
int 	ft_count_word_len(const char *line);
void    ft_update_token_type(t_token *lst);

/*parsing*/
void	clear_quote(char **word, t_env *env, int exit_code, t_mini *mini);
char	*ft_combine(t_token *lst);
void    ft_parsing(t_mini *mini, t_token *lst);

/*parsing quotes*/
int		ft_count_quote_len(char  *string);
t_token	*ft_break_string(char *string);
void	process_quote(char	**word);
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
void	free_single_token(t_token *token);
void	ft_token_free_lst(t_token *lst);

/*cmd list function*/
void	free_cmd(t_cmd *cmd);
t_cmd	*ft_lstnew_cmd(t_token *tokens);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void	free_cmd_list(t_cmd **lst);
int		ft_lstsize_cmd(t_cmd *lst);

/*create cmd table for execution*/
t_token	*remove_current_token(t_token *prev, t_token *token);
t_cmd	*split_into_simplecmds(t_token *tokens);
t_cmd	**lst_to_arr(t_cmd *lst);
t_cmd	**create_cmd_arr(t_token *tokens);

// EXEC
int		ft_exec(t_cmd **cmd_list, t_env *env, int old_exit, t_mini *msh);
void	ft_exec_msh_free(t_mini *msh);
// exec_utils
void	ft_close_all(t_cmd **cmd);
void	ft_free_char_vector(char **args);
int		ft_error(char *name, int type, int exit_code);
void	ft_free_all(t_cmd **cmd_list, t_env *env);
void	ft_free_char_vector_index(char **vector, int i);
int		ft_str_contains_char(char *str, char c);
void	ft_dup(t_cmd **cmd_list, int i, int single_flag);
void	ft_ambig(char *str);
int		find_space(char *word);
// exec_set_io
int		ft_set_io(t_cmd **cmd, int i, int single_flag);
int		ft_hdoc_write(char *str, int *pipe_ends);
void	ft_hdoc_sig(char *limitor);
// exec_set_io_heredoc
int		ft_set_hdoc(t_cmd **cmd_list);
// exec_pipeline
int		ft_child(t_cmd **cmd_list, int i, t_env *env, int single_flag);
int		ft_pipeline(t_cmd **cmd_list, int cmd_amt, t_env *env, t_mini *msh);
// exec_child_path
char	*ft_find_cmd_path(char *cmd_name, t_env *env);
// exec_child_args
char	**ft_make_args(t_token *tokens);
int		ft_get_arg_amnt(t_token *tokens);
// buildin
int		ft_is_buildin(t_token *tokens);
int		ft_do_buildin(char **args, t_env *env, t_cmd **list, int i);
int		ft_cd(char **args, t_env *env, int fd);
int		ft_echo(char **args, int fd);
int		ft_env(char **args, t_env *env, int fd);
int		ft_export(char **args, t_env *env, int fd);
int		ft_pwd(int fd);
int		ft_unset(char **args, t_env *env);
int		ft_exit(char **args, t_cmd **cmd_list, int i);
// env_utils
t_env	*ft_new_env_node(char *s);
void	ft_add_env(t_env *lst, t_env *new);
int		ft_add_to_msh_env(t_env *env, char *new_str);
t_env	*ft_find_in_env(t_env *env, char *target, int len);
size_t	size_env(t_env *lst);
char	*env_to_str(t_env *lst);
char	**create_env_arr(t_env *env);

int		exit_minishell(t_mini *mini, int exit_status);

/*Printf for checking progress*/
void    ft_print_token_lst(t_token *token_lst);
void    ft_print_env_list(t_env *env);
void	print_cmd(t_cmd **arr);

#endif
