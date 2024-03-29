/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:07:53 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/23 11:23:07 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

unsigned long	hash_function(char *key)
{
	unsigned long	i;
	int				j;

	i = 0;
	j = 0;
	while (key[j])
	{
		i += key[j];
		j++;
	}
	return (i % TABLE_SIZE);
}

t_hash_table	*create_hash_table(int size)
{
	t_hash_table	*table;
	int				i;

	i = 0;
	table = (t_hash_table *)malloc(sizeof(t_hash_table));
	table->size = size;
	table->count = 0;
	table->item = (t_hash_item **)ft_calloc(sizeof(t_hash_item *), size);
	while (i < table->size)
	{
		table->item[i] = NULL;
		i++;
	}
	return (table);
}

void	hash_insert_equals(char **str)
{
	int		i;
	char	*aux;

	i = 1;
	while (str[i])
	{
		if (str[i + 1] != NULL)
		{
			aux = ft_strdup(str[i]);
			free(str[i]);
			str[i] = ft_strjoin(aux, "=");
			free(aux);
		}
		if (i > 1)
		{
			aux = ft_strdup(str[1]);
			free(str[1]);
			str[1] = ft_strjoin(aux, str[i]);
			free(aux);
		}
		i++;
	}
}

t_hash_table	*hash_population(t_hash_table **table)
{
	char	**str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	(*table) = create_hash_table(TABLE_SIZE);
	while (__environ[len])
		len++;
	populate_env(*table, len);
	while (__environ[i])
	{
		str = ft_split(__environ[i], '=');
		if (count_equals_chr(__environ[i], '=') > 1)
			hash_insert_equals(str);
		if (str[0] != NULL && str[1] != NULL)
			hash_insert(table, str[0], str[1]);
		else if (str[0] != NULL)
			hash_insert(table, str[0], "");
		i++;
		free_split(str);
	}
	return (*table);
}
