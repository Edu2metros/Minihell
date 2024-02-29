/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:07:53 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/29 19:49:15 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_hash_table	*create_hash_table(int size)
{
	t_hash_table	*table;
	int				i;
	
	i = 0;
	table = (t_hash_table *) malloc(sizeof(t_hash_table));
	table->size = size;
	table->count = 0;
	table->item = (t_hash_item **) calloc(sizeof(t_hash_item), size);
	while (i < table->size)
	{
		table->item[i] = NULL;
		i++;
	}
	return (table);
}

t_hash_item	*create_item(char *key, char *value)
{
	t_hash_item	*item;

	item = (t_hash_item *)malloc(sizeof(t_hash_item));
	item->key = ft_strdup (key);
	item->value = ft_strdup (value);
	item->next = NULL;
	return (item);
}

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
	free ((*table)->item);
	free (*table);
}

void	print_table(t_hash_table **table)
{
	t_hash_item	*item;
	t_hash_item	*aux;
	int			index;
	int			i;

	i = 0;
	index = 0;
	item = NULL;
	while (i < (*table)->size)
	{
		if ((*table)->item[i])
		{
			item = (*table)->item[i];
			while (item != NULL)
			{
				aux = item->next;
				if (item->key =! NULL)
					printf("Key: %s, Value: %s\n", (*table)->item[i]->key, (*table)->item[i]->value);
				item = aux;
				index++;
			}
			index++;
		}
		i++;
	}
}

unsigned long hash_function(char *input)
{
	unsigned long	i;
	int				j;
	
	i = 0;
	j = 0;
	while (input[j])
	{
		i += input[j];
		j++;
	}
	return (i % TABLE_SIZE);
}