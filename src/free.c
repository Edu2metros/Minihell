/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:07:39 by eddos-sa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/16 18:58:34 by eddos-sa         ###   ########.fr       */
=======
/*   Updated: 2024/03/16 18:11:01 by jaqribei         ###   ########.fr       */
>>>>>>> 09936e87005442f04853962545fd3648df6b2282
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lstclear_cmd(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		i = 0;
		if(current->name != NULL)
			free(current->name);
		if (current->args != NULL)
		{
			while (current->args[i] != NULL)
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
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

void	free_redirect_in(t_redirect_in **redirect)
{
	t_redirect_in	*current;
	t_redirect_in	*next;

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
}

void free_hashs(t_hash_table *hash)
{
	int i;
	i = 0;
	while(i < hash->size) // free na tabela hash item
	{
		if (hash->item[i] != NULL)
		{
			free(hash->item[i]->key);
			if(hash->item[i]->value != NULL)
				free(hash->item[i]->value);
			free(hash->item[i]);
		}
		i++;
	}
	free_split(hash->env);
}