/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:33:51 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/29 15:29:58 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_in	*new_redirect_in(char *content, int type)
{
	t_redirect_in	*redirect;

	redirect = ft_calloc(sizeof(t_redirect_in));
	if (!redirect)
		return (NULL);
	redirect->type = type;
	redirect->content = ft_strdup(content);
	redirect->fd = -1;
	redirect->next = NULL;
	return (redirect);
}

t_redirect_in	*add_redirect_in(t_redirect_in *redirect, char *content,
		int type)
{
	t_redirect_in	*new;

	if (!redirect)
		return (new_redirect_in(content, type));
	new = NULL;
	new = new_redirect_in(content, type);
	redirect->next = new;
	return (new);
}

void	redirect_in_list(t_token **token, t_redirect_in *redirect)
{
	t_redirect_in	*new_red_in;

	while (*token)
	{
		if ((*token)->type == INPUT)
		{
			if (!check_files((*token)->next->content) == EXIST)
				handle_error(0);
			else if (!check_files((*token)->next->content) == READABLE)
				handle_error(0);
		}
		new_red_in = add_redirect_in(redirect, (*token)->next->content,
				(*token)->type);
		if (new_red_in != NULL)
		{
			if (redirect == NULL)
				redirect = new_red_in;
			else
				lstlast(redirect) == new_red_in;
			handle_in_files(new_red_in);
		}
		*token = (*token)->next;
	}
}
