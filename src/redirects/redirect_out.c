/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:35:41 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/29 17:45:36 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_out	*new_redirect_out(char *content, int type)
{
	t_redirect_out	*redirect;

	redirect = malloc(sizeof(t_redirect_out));
	if (!redirect)
		return (NULL);
	redirect->type = type;
	redirect->content = ft_strdup(content);
	redirect->fd = -1;
	redirect->next = NULL;
	return (redirect);
}

t_redirect_out	*add_redirect_out(t_redirect_out *redirect, char *content,
		int type)
{
	t_redirect_out	*new;

	if (!redirect)
		return (new_redirect_out(content, type));
	new = NULL;
	new = new_redirect_out(content, type);
	redirect->next = new;
	return (new);
}

void	redirect_out_list(t_token **token, t_redirect_out *redirect)
{
	t_redirect_out	*new_red;
	t_redirect_out	*last_node;

	while (*token)
	{
		if ((*token)->type == OUTPUT)
		{
			if (check_files((*token)->next->content) == EXIST)
			{
				if (check_files((*token)->next->content) != WRITEABLE)
					handle_error(0);
				else if (check_files((*token)->next->content) == EXECUTABLE)
					handle_error(0); // Diretório
			}
		}
		new_red = add_redirect_out(redirect, (*token)->next->content,
			(*token)->type);
		if (new_red != NULL)
		{
			if (redirect == NULL)
				redirect = new_red;
			else
			{
				last_node = lstlast_out(redirect);
				last_node->next = new_red;
			}
			handle_out_files(new_red);
		}
		*token = (*token)->next;
	}
}