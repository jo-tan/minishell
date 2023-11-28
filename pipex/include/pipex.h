/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:42:38 by aauthier          #+#    #+#             */
/*   Updated: 2023/11/28 15:50:25 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define USAGE "Usage : ./pipex infile cmd1 | cmd2 > outfile"
# include <string.h>

typedef enum e_result
{
	ERROR,
	OK
}				t_result;

typedef enum e_error
{
	TOO_FEW_ARG_ERROR,
	TOO_MANY_ARG_ERROR
}			t_error;

typedef struct s_var
{
	char	*var_path;
	char	*var_temp;
	char	*cmd_path;
	size_t	len;
}				t_var;

typedef struct s_params
{
	char		**argv;
	int			pipefd[2];
	char *const	*env;
}				t_params;

// size_t		ft_strlen(const char *s);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);

// int			ft_putstr_fd(char *s, int fd);
char		*ft_strchr(const char *s, int c);
?int		ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strncpy(char *dest, const char *src, size_t n);

char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnjoin_wsep(char const *s1, char const *s2, size_t ns2,
				char *sep);

char		**ft_split(char *str, char *charset);
void		*ft_calloc(size_t count, size_t size);


// To include in minishell.h
t_result	child_a(int infile, t_params *params);
t_result	child_b(int outfile, t_params *params);
void		pipex(int infile, int outfile, t_params *params);

char		*find_var_path(char *const env[]);
char		*find_cmd(char *cmd, char *const env[]);
char		*access_cmd(int *errcode, char *cmd_path);
t_result	error(t_error error_code);
t_result	print_path_cmd_error(char *cmd, int errcode);

#endif


? replace but used in minishell
// no need to replace