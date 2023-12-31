/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jo-tan <jo-tan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:26:22 by jo-tan            #+#    #+#             */
/*   Updated: 2023/11/13 18:26:25 by jo-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_print_token_lst(t_token *token_lst)
{
    t_token *p;
    char    *type;

    p = token_lst;
    while (p)
    {
        if (p->type == NONE)
            type = "NONE";
        if (p->type == ARG)
            type = "ARG";
        if (p->type == PIPE)
            type = "PIPE";
        if (p->type == FILE_IN)
            type = "FILE_IN";
        if (p->type == HERE_DOC)
            type = "HERE_DOC";
        if (p->type == FILE_OUT)
            type = "FILE_OUT";
        if (p->type == FILE_OUT_AP)
            type = "FILE_OUT_AP";

        printf("❮%d%s/%s❯   ", p->type, type, p->word);
        p = p->next;
    }
    printf("\n");
}

void    ft_print_env_list(t_env *env)
{
    t_env   *p;
    int     i = 0;

    p = env;
    while (p)
    {
        printf("❮line: %i/%s❯\n", i + 1, p->line);
        i++;
        p = p->next;
    }
}

void	print_cmd(t_cmd **arr)
{
    printf("------------CMD Table--------------\n");
	while (*arr)
	{
		printf("--------------------------\n");
		ft_print_token_lst((*arr)->tokens);
		++arr;
	}
	printf("--------------------------\n");
}