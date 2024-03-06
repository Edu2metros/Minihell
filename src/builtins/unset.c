/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:24:26 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/06 20:39:25 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void hash_delete(t_hash_table *table, char *key)
{
	int i;
	t_hash_item *temp_item;
	t_hash_item *prev_item;
	
	i = 0;
	while(i < table->size)
	{
		temp_item = table->item[i];
		while(temp_item != NULL)
		{
			if(ft_strncmp(temp_item->key, key, ft_strlen(key)) == 0)
			{
				if(prev_item != NULL)
					prev_item->next = temp_item->next;
				else
					table->item[i] = temp_item->next;
				free(temp_item->key);
				free(temp_item->value);
				free(temp_item);
				return ;
			}
			prev_item = temp_item;
			temp_item = temp_item->next;
		}
		i++;
	}
	
}

void unset(t_minishell *mini, t_cmd *cmd)
{
	int i;
	i = 1;
	if(ft_array_len(cmd->args) == 1)
		printf("unset: not enough arguments (colocar isso daqui no fd)\n");
	else
	{
		while(cmd->args[i])
		{
			if(hash_search(mini->table, cmd->args[i] != NULL))
				hash_delete(mini->table, cmd->args[i]);
			i++;
		}
	}
}
