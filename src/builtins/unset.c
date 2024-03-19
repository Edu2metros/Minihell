/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:24:26 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 11:38:13 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_variable_env(t_hash_table *table, char *key)
{
	int	i;

	i = 0;
	while (table->env[i])
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
	t_hash_item	*item;
	int			index;

	index = hash_function(key);
	item = table->item[index];
	while (item != NULL)
	{
		if (item->key && !ft_strncmp(item->key, key, ft_strlen(key) + 1))
		{
			free(item->key);
			free(item->value);
			free(item);
			table->item[index] = NULL;
			delete_variable_env(table, key);
			break ;
		}
		item = item->next;
	}
	get_control()->return_status = 0;
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
	if (cmd->on_fork == 1)
		exit(get_control()->return_status);
}
