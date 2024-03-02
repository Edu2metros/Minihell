/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:07:53 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/02 17:07:12 by  jaqribei        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp_len(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2))
		return (ft_strncmp(s1, s2, __UINT64_MAX__) == 0);
	return (0);
}

unsigned long hash_function(char *key)
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

t_hash_table	*hash_population(t_minishell *mini, t_hash_table **table)
{
	char	**str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	(*table) = create_hash_table(TABLE_SIZE);
	while(__environ[len])
		len++;
	while(__environ[i])
	{
		str = ft_split(__environ[i], '=');
		if(str[0] != NULL && str[1] != NULL)
			hash_insert(table, str[0], str[1]);
		else if (str[0] != NULL)
			hash_insert(table, str[0], "");
		i++;
	}
	return (*table);
}