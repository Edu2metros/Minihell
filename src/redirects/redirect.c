/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:12:19 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/06 20:13:57 by eddos-sa         ###   ########.fr       */
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


void	clear_token_node(t_token **token_list, t_token *target_tkn)
{
	t_token	*current_tkn;

	current_tkn = *token_list;
	while (current_tkn)
	{
		if (current_tkn == target_tkn)
		{
			if (current_tkn->previous)
				current_tkn->previous->next = current_tkn->next;
			else
				*token_list = current_tkn->next;
			if (current_tkn->next)
				current_tkn->next->previous = current_tkn->previous;
			free(current_tkn->content);
			free(current_tkn);
			break ;
		}
		current_tkn = current_tkn->next;
	}
}

void	handle_redirects(t_minishell *mini)
{
	t_token	*token;
	t_token	*aux;

	token = mini->token;
	// if (token && token->type == PIPE)
	// 	free(token);
	while (token && token->type != PIPE)
	{
		aux = token->next;
		if (token->type == OUTPUT || token->type == INPUT
			|| token->type == APPEND || token->type == HEREDOC && (aux != NULL))
		{
			if (token->type == HEREDOC)
			{
				redirect_in_list(&token, &mini->redirect_list_in);
				hand_heredoc(mini);
			}
			if (token->type == INPUT)
				redirect_in_list(&token, &mini->redirect_list_in);
			else if (token->type == OUTPUT || token->type == APPEND)
				redirect_out_list(&token, &mini->redirect_list_out);
			clear_token_node(&mini->token, token->next);
			clear_token_node(&mini->token, token->next); //don't delete this, too much important, don't work without this line
			print_tokens(mini);
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