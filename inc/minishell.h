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
# include "../libft/libft.h"

enum    e_token
{
    WORD = -1,
    EMPTY_SPACE = ' ',
    NEXT_LINE = '\n',
    QUOTE = '\'',
    DQUOTE = '\"',
    PIPE = '|',
    REDIR_IN = '<',
    REDIR_OUT = '>',
    ENV = '$',
} ;

// To parse a string like: env > file | cat -e file | grep PID
// the command table will look like
// cmd[0] = {env, 3, >, file} redirect to find or create "file" and input result of env to file **remember to unlink(file)
// cmd[1] = {cat, 3, -e, file}
// cmd[2] = {grep, 4, PID}
// check syntex error before execute any cmd, if error, print error msg, return error num?
void    change_signal(void);

#endif

/*Parsing test:
o-tan@made-f0Cr5s1:~/Documents/minishell$ export hi='ls     -l '
jo-tan@made-f0Cr5s1:~/Documents/minishell$ $hi'a'
ls: cannot access 'a': No such file or directory
jo-tan@made-f0Cr5s1:~/Documents/minishell$ ls -l a
ls: cannot access 'a': No such file or directory
jo-tan@made-f0Cr5s1:~/Documents/minishell$ >$hi
bash: $hi: ambiguous redirect
jo-tan@made-f0Cr5s1:~/Documents/minishell$ >"$hi"
jo-tan@made-f0Cr5s1:~/Documents/minishell$ << $hi
> sldkjf
> sldkj
> $hi
jo-tan@made-f0Cr5s1:~/Documents/minishell$ echo $hi
ls -l
jo-tan@made-f0Cr5s1:~/Documents/minishell$ << $hi
sldkjf
sldkj
$hi
jo-tan@made-f0Cr5s1:~/Documents/minishell$ << $hi
> ls -l
> $hi
jo-tan@made-f0Cr5s1:~/Documents/minishell$ cat <<$hi
> $USER
> $hi
jo-tan
jo-tan@made-f0Cr5s1:~/Documents/minishell$ cat <<$hi""
> $USER
> $hi
$USER
*/