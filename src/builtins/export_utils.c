/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:45:14 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/18 20:58:32 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hash_update_value(t_hash_table *hash, char *key)
{
	char	*equal_pos;
	int		key_length;
	int		i;

	equal_pos = ft_strchr(key, '=');
	if (equal_pos == NULL)
		equal_pos = 0;
	i = 0;
	while (i < hash->size)
	{
		if (hash->item[i])
		{
			key_length = equal_pos - key;
			if (ft_strncmp(hash->item[i]->key, key, key_length) == 0)
			{
				free(hash->item[i]->value);
				if (equal_pos == 0)
					hash->item[i]->value = ft_strdup("");
				else
					hash->item[i]->value = ft_strdup(equal_pos + 1);
				break ;
			}
		}
		i++;
	}
}

int	ft_is_stralnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isall_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_' && str[0] != '=')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

int	validate_string(char *str)
{
	if (!str || !str[0])
	{
		ft_printf_fd(STDERR_FILENO, "minishell: export: argumento vazio\n");
		get_control()->return_status = 1;
		return (0);
	}
	if (!is_valid_identifier(str))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: export: `%s': not a valid \
		identifier\n", str);
		get_control()->return_status = 1;
		return (0);
	}
	return (1);
}
