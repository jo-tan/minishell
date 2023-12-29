#include "minishell.h"

int	ft_pwd(int fd)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (ft_error("pwd", 0, 1));
	write(fd, current_dir, ft_strlen(current_dir));
	write(fd, "\n", 1);
	free(current_dir);
	return (0);
}
