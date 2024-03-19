/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:58:15 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 17:10:20 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_item(t_hash_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

void	free_table(t_hash_table **table)
{
	t_hash_item	*item;
	t_hash_item	*aux;
	int			i;

	i = 0;
	while (i < (*table)->size)
	{
		item = (*table)->item[i];
		while (item != NULL)
		{
			aux = item->next;
			free_item(item);
			item = aux;
		}
		i++;
	}
	i = 0;
	while ((*table)->env[i] != NULL)
	{
		free((*table)->env[i]);
		i++;
	}
	free ((*table)->env);
	free ((*table)->item);
	free (*table);
}

void	erase_node(t_hash_table **table, t_hash_item *item, char *key)
{
	t_hash_item	*aux;
	t_hash_item	*item_prev;

	aux = NULL;
	item_prev = item;
	while (item_prev && ft_strncmp(item_prev->key, key, (ft_strlen(key) + 1)))
	{
		aux = item_prev;
		item_prev = item_prev->next;
	}
	if (item_prev && aux)
	{
		aux->next = item_prev->next;
		free_item(item_prev);
		(*table)->count--;
	}
}

void	erase_table(t_hash_table **table, char *key)
{
	t_hash_item	*item;
	int			index;

	index = hash_function(key);
	item = (*table)->item[index];
	if (item->next == NULL)
	{
		free_item(item);
		(*table)->item[index] = NULL;
		(*table)->count--;
	}
	else if (item->next != NULL)
		erase_node(table, item, key);
}

void	free_hashs(t_hash_table *hash)
{
	int	i;

	i = 0;
	while (i < hash->size)
	{
		if (hash->item[i] != NULL)
		{
			free(hash->item[i]->key);
			if (hash->item[i]->value != NULL)
				free(hash->item[i]->value);
			free(hash->item[i]);
		}
		i++;
	}
	free_split(hash->env);
}
