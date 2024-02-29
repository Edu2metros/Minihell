/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:12:19 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/29 17:46:09 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_out	*lstlast_out(t_redirect_out *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_redirect_in	*lstlast_in(t_redirect_in *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
void	handle_redirects(t_minishell *mini)
{
	t_token		*token;
	t_token		*aux;

	token = get_control()->token;
	while (token && token->type != PIPE)
	{
		aux = token->next;
		if (is_redirect(mini) && (aux != NULL))
		{
			if (token->type == INPUT)
				redirect_in_list(&token, get_control()->redirect_list_in);
			else if (token->type == OUTPUT || token->type == APPEND)
				redirect_out_list(&token, get_control()->redirect_list_out);
		}
		token = aux;
	}
}
