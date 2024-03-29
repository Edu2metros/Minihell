/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:12:19 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 20:43:07 by eddos-sa         ###   ########.fr       */
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

void	handle_redirects(t_minishell *mini)
{
	t_token	*token;
	t_token	*aux;
	t_cmd	*cmd;

	cmd = lst_first(mini->cmd);
	token = mini->token;
	while (token)
	{
		aux = token->next;
		if (token->type == is_redirect(token) && (aux != NULL))
		{
			if (token->type == HEREDOC)
				set_heredoc(&token, &cmd->redirect_list_in, cmd);
			if (token->type == INPUT)
				redirect_in_list(&token, &cmd->redirect_list_in, cmd);
			else if (token->type == OUTPUT || token->type == APPEND)
				redirect_out_list(&token, &cmd->redirect_list_out, cmd);
			token = aux;
		}
		if (token->type == PIPE)
			cmd = cmd->next;
		token = aux;
	}
}

t_redirect_in	*lst_first_in(t_redirect_in *redirect)
{
	t_redirect_in	*result;

	result = redirect;
	while (result != NULL && result->previous != NULL)
		result = result->previous;
	return (result);
}
