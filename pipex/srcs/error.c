/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauthier <aauthier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 20:21:23 by aauthier          #+#    #+#             */
/*   Updated: 2022/02/01 20:30:59 by aauthier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

static char	*get_str_error(t_error error_code)
{
	char	*str;

	if (error_code == TOO_FEW_ARG_ERROR)
		str = "Too few arguments. \n" USAGE;
	if (error_code == TOO_MANY_ARG_ERROR)
		str = "Too many arguments. \n" USAGE;
	return (str);
}

t_result	error(t_error error_code)
{
	char	*str;

	str = get_str_error(error_code);
	printf("%s\n", str);
	return (ERROR);
}
