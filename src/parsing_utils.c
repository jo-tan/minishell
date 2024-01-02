/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:55:10 by jo-tan            #+#    #+#             */
/*   Updated: 2024/01/02 11:46:30 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (ft_isspace(*str))
		++str;
	return (str);
}

int	end_of_cmd(int c)
{
	return (c == 0 || c == '#');
}
