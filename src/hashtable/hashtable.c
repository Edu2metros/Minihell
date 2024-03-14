/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:07:53 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/14 16:31:47 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp_len(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2))
		return (ft_strncmp(s1, s2, __UINT64_MAX__) == 0);
	return (0);
}

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
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
	table = (t_hash_table *)ft_calloc(1, sizeof(t_hash_table));
	table->size = size + 1;
	table->count = 0;
	table->item = (t_hash_item **)ft_calloc(sizeof(t_hash_item) + 1, size);
	while (i < table->size)
	{
		table->item[i] = NULL;
		i++;
	}
	return (table);
}
int	count_equals_chr(char *str, char c)
{
	int	i;
	int	equals;

	i = 0;
	equals = 0;
	if (str == NULL || *str == '\0')
		return (equals);
	while (str[i])
	{
		if(str[i] == c)
			equals++;
		i++;
	}
	return (equals);
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
		if (count_equals_chr(__environ[i], '=') > 1)
			hash_insert_equals(str);
		if(str[0] != NULL && str[1] != NULL)
			hash_insert(table, str[0], str[1]);
		else if (str[0] != NULL)
			hash_insert(table, str[0], "");
		i++;
		free_split(str);
	}
	return (*table);
}
