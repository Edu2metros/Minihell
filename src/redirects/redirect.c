/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:12:19 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/05 18:27:40 by jaqribei         ###   ########.fr       */
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

	token = mini->token;
	// if (token && token->type == PIPE)
		//maybe erase pipe
	while (token && token->type != PIPE)
	{
		aux = token->next;
		if (token->type == OUTPUT || token->type == INPUT || token->type == APPEND || token->type == HEREDOC && (aux != NULL))
		{
			// if (token->type == HEREDOC)
			// 	deal with it
			if (token->type == INPUT)
				redirect_in_list(&token, &mini->redirect_list_in);
			else if (token->type == OUTPUT || token->type == APPEND)
				redirect_out_list(&token, &mini->redirect_list_out);
			// aux = token->next->next;
			//maybe remove token and token next
			
		}
		token = aux;
	}
}
