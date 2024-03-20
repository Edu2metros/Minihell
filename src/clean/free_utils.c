/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:55:47 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/20 15:06:15 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	current = *cmd;
	while (current != NULL)
	{
		i = 0;
		next = current->next;
		if (current->name != NULL && *current->name != '\0')
			free(current->name);
		while (current->args[i] != NULL)
		{
			free(current->args[i]);
			i++;
		}
		free(current->args);
		free(current);
		current = next;
	}
	*cmd = NULL;
}

void	free_all(t_minishell *minishell)
{
	free_tokens(&(minishell->token));
	lstclear_cmd(&(minishell->cmd));
	free_redirect_in(&(minishell->redirect_list_in));
	free_redirect_out(&(minishell->redirect_list_out));
	close_fd();
}

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

void	free_redirect_in(t_redirect_in **redirect)
{
	t_redirect_in	*current;
	t_redirect_in	*next;

	current = lst_first_in(*redirect);
	if (current != NULL)
		close_fd();
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*redirect = NULL;
}

void	free_redirect_out(t_redirect_out **redirect)
{
	t_redirect_out	*current;
	t_redirect_out	*next;

	current = *redirect;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*redirect = NULL;
}
