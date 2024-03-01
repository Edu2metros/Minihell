/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:02:12 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/01 16:55:38 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
				if (item->key != NULL)
					printf("Key: %s, Value: %s\n", (*table)->item[i]->key, (*table)->item[i]->value);
				item = aux;
				index++;
			}
			index++;
		}
		i++;
	}
}
