/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:40:40 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/13 15:30:38 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_hash_item	*create_item(char *key, char *value)
{
	t_hash_item	*item;

	item = (t_hash_item *)malloc(sizeof(t_hash_item));
	item->key = ft_strdup (key);
	item->value = ft_strdup (value);
	item->next = NULL;
	return (item);
}

void	hand_hash_collision(t_hash_table **table, t_hash_item *item, int index)
{
	t_hash_item	*current;

	current = (*table)->item[index];
	while (current->next != NULL)
		current = current->next;
	current->next = item;
	current->next->next = NULL;
	(*table)->count++;
}

void	hash_insert(t_hash_table **table, char *key, char *value)
{
	t_hash_item	*item;
	t_hash_item	*current;
	int			index;

	item = create_item(key, value);
	index = hash_function(key);
	current = (*table)->item[index];
	
	if (current == NULL)
	{
		(*table)->item[index] = item;
		(*table)->count++;
	}
	else
	{
		if(current->key && (ft_strcmp_len(current->key, key)))
		{
			free(current->value);
			current->value = ft_strdup(value);
			free_item(item);
		}
		else
			hand_hash_collision(table, item, index);
	}
}

char	*hash_search(t_hash_table *table, char *key)
{
	t_hash_item	*item;
	int			index;
	
	index = hash_function(key);
	item = table->item[index];
	
	while (item != NULL)
	{
		if(item->key && !ft_strncmp(item->key, key, ft_strlen(key) + 1))
			return (ft_strdup(item->value));
		item = item->next;
	}
	return (NULL);
}
