/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:12:19 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/13 16:11:37 by eddos-sa         ###   ########.fr       */
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

t_token	*first(t_token **lst)
{
	while (lst != NULL && (*lst)->previous != NULL)
		lst = &(*lst)->previous;
	return (*lst);
}

void handle_redirects(t_cmd *cmd, t_minishell *mini)
{
	t_token *token;
	t_token *aux;

	token = mini->token;
	while (token)
	{
		aux = token->next;
		if (token->type == is_redirect(token) && (aux != NULL))
		{
			if (token->type == HEREDOC)
				set_heredoc(&token, &cmd->redirect_list_in);
			if (token->type == INPUT)
				redirect_in_list(&token, &cmd->redirect_list_in);
			else if (token->type == OUTPUT || token->type == APPEND)
				redirect_out_list(&token, &cmd->redirect_list_out);
			token = aux;
		}
		token = aux;
	}
}

void	close_fd(t_minishell *mini)
{
	t_redirect_out *aux_out;
	t_redirect_in *aux_in;

	aux_out = mini->redirect_list_out;
	aux_in = mini->redirect_list_in;
	while (aux_out)
	{
		close(aux_out->fd_out);
		aux_out = aux_out->next;
	}
	while (aux_in)
	{
		close(aux_in->fd_in);
		aux_in = aux_in->next;
	}
}
