/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:12:19 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/07 19:09:15 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_out *lstlast_out(t_redirect_out *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_redirect_in *lstlast_in(t_redirect_in *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_token *first(t_token **lst)
{
	while (lst != NULL && (*lst)->previous != NULL)
		lst = &(*lst)->previous;
	return (*lst);
}

void clear_token_redirect(t_token **token)
{
	t_token	*current;
	t_token	*last_node = NULL;  // Initialize last_node
	t_token	*aux;

	current = *token;

	while (current)
	{
		if (is_redirect(current) && current->next != NULL && (current->next->type == WORD || current->next->type == QUOTE))
		{
			aux = current->next;
			last_node->next = aux->next;
			
			// Free memory for current and aux
			free(current->content);
			free(current);
			free(aux->content);
			free(aux);

			current = last_node->next;
		}
		else
		{
			last_node = current;
			current = current->next;
		}
	}
}

void handle_redirects(t_minishell *mini)
{
	t_token *token;
	t_token *aux;

	token = mini->token;
	// if (token && token->type == PIPE)
	// 	free(token);
	while (token && token->type != PIPE)
	{
		aux = token->next;
		if (is_redirect(token) && (aux != NULL))
		{
			// if (token->type == HEREDOC)
			// {
			// 	redirect_in_list(&token, &mini->redirect_list_in);
			// 	hand_heredoc(mini);
			// }
			if (token->type == INPUT)
				redirect_in_list(&token, &mini->redirect_list_in);
			else if (token->type == OUTPUT || token->type == APPEND)
				redirect_out_list(&token, &mini->redirect_list_out);
			print_tokens(mini);
		}
		token = aux;
	}
			clear_token_redirect(&mini->token);
}

void close_fd(t_minishell *mini)
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