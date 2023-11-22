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
    char    *quote;

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
        if (p->type == OPEN_FILE)
            type = "OPEN_FILE";
        if (p->type == HERE_DOC)
            type = "HERE_DOC";
        if (p->type == HD_WORD)
            type = "HD_WORD";
        if (p->type == FILE_OUT)
            type = "FILE_OUT";
        if (p->type == EXIT_FILE)
            type = "EXIT_FILE";
        if (p->type == FILE_OUT_AP)
            type = "FILE_OUT_AP";
        if (p->type == EXIT_FILE_AP)
            type = "EXIT_FILE_AP";
        
        if (p->isquote == UNSET)
            quote = "UNSET";
        if (p->isquote == SINGLE)
            quote = "SINGLE";
        if (p->isquote == DOUBLE)
            quote = "DOUBLE";

        printf("❮%s/%s/%s❯   ", type, quote, p->word);
        p = p->next;
    }
    printf("\n");
}