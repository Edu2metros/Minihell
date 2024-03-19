/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:02:12 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 16:41:30 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_item(t_hash_item *item, int fd_out)
{
	t_hash_item	*current;
	t_hash_item	*aux;
	int			index;

	index = 0;
	current = item;
	while (current != NULL)
	{
		aux = current->next;
		if (ft_strcmp(current->key, "?") == 0)
		{
			current = aux;
			continue ;
		}
		if (current->key != NULL && (current->value != NULL
				&& ft_strcmp(current->value, "") != 0))
			ft_printf_fd(fd_out, "%s=%s\n", current->key, \
			current->value);
		if (ft_strncmp(current->key, "a", 1) == 0)
			ft_printf_fd(fd_out, "KEY: A posição: %i\n", index);
		current = aux;
		index++;
	}
}

void	print_table(t_hash_table **table, int fd_out)
{
	t_hash_item	*current;
	int			i;

	i = 0;
	current = NULL;
	if (table == NULL || *table == NULL)
		return ;
	while (i < (*table)->size)
	{
		if ((*table)->item[i])
		{
			current = (*table)->item[i];
			print_item(current, fd_out);
		}
		i++;
	}
}

int	ft_strcmp_len(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2))
		return (ft_strncmp(s1, s2, __UINT64_MAX__) == 0);
	return (0);
}

void	populate_env(t_hash_table *table, int len)
{
	int	i;

	i = 0;
	table->env = (char **)ft_calloc(sizeof(char *), len + 1);
	while (i < len)
	{
		table->env[i] = ft_strdup(__environ[i]);
		i++;
	}
	table->env[i] = NULL;
}