#include "minishell.h"

int get_var_len(char *p)
{
    int var_len;

    var_len = 0;
    while (ft_isenvname(p[var_len]) == 1)
        var_len++;
    return (var_len);
}

/*char	*get_env_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(arg, env_name) == 0)
		{
			ft_memdel(env_val);
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}*/

char    *copy_var_name(char *p, int exit_code)
{
    int var_len;
    int i;
    char   *var_name; 

    var_len = get_var_len(p);
    i = 0;
    var_name = malloc(sizeof(char) * var_len + 1);
    if (!var_name)
        return (NULL); //handle malloc failure
    if (p[0] == '?')
	{
		var_name = ft_itoa(exit_code);
		return (var_name);
	}
	if (ft_isdigit(p[0]))
		return (NULL);
    while (i != var_len)
    {
        var_name[i] = p[i];
        i++;
    }
    var_name[i] = '\0';
    printf("ft_var: %s\n", var_name);
    return (var_name);
}

/*char	*get_var_value(const char *arg, char *var_name, t_env *env, int ret)
{
	char	*var_value;
	int		i;

	i = 0;
	if (arg[0] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);
	}
	if (ft_isdigit(arg[0]))
		return (NULL);
	while (arg[0] && is_env_char(arg[0]) == 1 && i < )
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	return (var_value);
}*/

void    expansion(char **word, t_env *env, int exit_code)
{
    char *p;
    char *var_name;

    p = *word;
    while (*p != '\0')
	{
		if (*p == '$')
		{
			p++;
			var_name = copy_var_name(p, exit_code);
			printf("var_name: %s\n", var_name);
			free(var_name);
			p += get_var_len(p);
		}
		p++;
	}
	(void)env;
}