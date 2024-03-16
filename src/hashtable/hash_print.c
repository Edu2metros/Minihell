/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:02:12 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/15 22:50:29 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    print_table(t_hash_table **table, int fd_out)
{
    t_hash_item    *current;
    t_hash_item    *aux;
    int            index;
    int            i;

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
								if (ft_strcmp(current->key, "?") == 0)
				{
					current = aux;
					continue ;
				}
                if (current->key != NULL && (current->value != NULL && ft_strcmp(current->value, "") != 0))
                    ft_printf_fd(fd_out, "%s=%s\n", current->key, current->value);
                if(ft_strncmp(current->key, "a", 1) == 0)
                    ft_printf_fd(fd_out, "KEY: A posição: %i\n", index);
                current = aux;
                index++;
            }
            index++;
        }
        i++;
    }
}
