/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:07:39 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/20 10:39:02 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_args(t_cmd *current, int i)
{
	while (current->args[i] != NULL)
	{
		free(current->args[i]);
		i++;
	}
	free(current->args);
}

void	lstclear_cmd(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	if (lst == NULL || *lst == NULL)
		return ;
	current = lst_first(*lst);
	while (current != NULL)
	{
		i = 0;
		if (current->name != NULL)
			free(current->name);
		if (current->args != NULL)
			free_args(current, i);
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	free_tokens(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (*token == NULL || (*token)->content == NULL)
		return ;
	current = *token;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	free_reds(t_cmd *aux)
{
	aux = lst_first(aux);
	while (aux)
	{
		if (aux->redirect_list_in)
			free_redirect_in(&aux->redirect_list_in);
		if (aux->redirect_list_out)
			free_redirect_out(&aux->redirect_list_out);
		aux = aux->next;
	}
}
