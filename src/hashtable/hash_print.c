/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:02:12 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/03 02:55:43 by  jaqribei        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_table(t_hash_table **table)
{
	t_hash_item	*current;
	t_hash_item	*aux;
	int			index;
	int			i;

	i = 0;
	index = 0;
	current = NULL;
	if(table == NULL || *table == NULL)
		return ;
	while (i < (*table)->size)
	{
		if ((*table)->item[i])
		{
			current = (*table)->item[i];
			while (current != NULL)
			{
				aux = current->next;
				if (current->key != NULL && current->value != NULL)
					printf("Key: %s, Value: %s\n", current->key, current->value);
				current = aux;
				index++;
			}
			index++;
		}
		i++;
	}
}
