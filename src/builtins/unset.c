/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:24:26 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/16 12:55:54 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void delete_variable_env(t_hash_table *table, char *key)
{
	int i;
	i = 0;

	while(table->env[i])
	{
		if (ft_strcmp(table->env[i], key) == 0)
		{
			free(table->env[i]);
			shift_args(table->env, i);
			break ;
		}
		i++;
	}
}

void	hash_delete(t_hash_table *table, char *key)
{
	int			i;

	i = 0;
	while (i < table->size)
	{
		if(table->item[i])
		{
			if (ft_strcmp(table->item[i]->key, key) == 0)
			{
				delete_variable_env(table, key);
				free(table->item[i]->key);
				free(table->item[i]->value);
				free(table->item[i]);
				table->item[i] = NULL;
				table->count--;
				break ;
			}
		}
		i++;
	}
}

void	unset(t_minishell *mini, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (ft_array_len(cmd->args) == 1)
		get_control()->return_status = 0;
	else
	{
		while (cmd->args[i])
		{
			if (hash_search(mini->table, cmd->args[i]) != NULL)
				hash_delete(mini->table, cmd->args[i]);
			i++;
		}
	}
}
