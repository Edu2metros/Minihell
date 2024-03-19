/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exports_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:55:44 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/18 21:03:15 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_equals(char *str)
{
	int	i;
	int	equal_count;

	i = 0;
	equal_count = 0;
	while (str[i])
	{
		if (str[i] == '=')
			equal_count++;
		i++;
	}
	if (equal_count != 1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: export: `%s': too many or no \
		equal sign (=)\n", str);
		get_control()->return_status = 1;
		return (0);
	}
	return (1);
}

int	check_error(char *str, t_hash_table *hash)
{
	if (!validate_string(str))
		return (0);
	if (!count_equals(str))
		return (0);
	return (1);
}

void	extract_key_value(char *arg, char **key, char **value)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos == NULL)
	{
		*key = ft_strdup(arg);
		*value = ft_strdup("");
	}
	else
	{
		*key = ft_substr(arg, 0, equal_pos - arg);
		*value = ft_strdup(equal_pos + 1);
		if (!(*value))
			*value = ft_strdup("");
	}
}

void	process_args(t_cmd *cmd, t_hash_table *hash, int i)
{
	char	*key;
	char	*value;

	while (cmd->args[i])
	{
		if (hash_search(hash, cmd->args[i]) != NULL)
			hash_update_value(hash, cmd->args[i]);
		else if (check_error(cmd->args[i], hash))
		{
			extract_key_value(cmd->args[i], &key, &value);
			hash_insert(&hash, key, value);
			free(key);
			if (value)
				free(value);
			get_control()->return_status = 0;
		}
		i++;
	}
}

void	export(t_cmd *cmd, t_hash_table *hash)
{
	int	i;

	i = 1;
	if (ft_array_len(cmd->args) == 1)
		print_export(hash, cmd);
	else
	{
		process_args(cmd, hash, i);
	}
	if (get_control()->cmd->on_fork == 1)
		exit(get_control()->return_status);
}
