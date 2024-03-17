/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:01:10 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/17 14:40:22 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

void	print_n_free(t_export *export)
{
	t_export	*temp_export;
	t_export	*next_export;
	int			fd_out;

	fd_out = 1;
	temp_export = export;
	get_control()->redirect_list_out = lstlast_out(get_control()->cmd->redirect_list_out);
	if (get_control()->cmd->redirect_list_out)
		fd_out = get_control()->cmd->redirect_list_out->fd_out;
	while (temp_export != NULL)
	{
		if (!ft_strncmp(temp_export->value, "", 1))
			ft_printf_fd(fd_out, "declare -x %s\n", temp_export->key);
		// printf("declare -x %s\n", temp_export->key);
		else
			ft_printf_fd(fd_out, "declare -x %s=\"%s\"\n", temp_export->key,
				temp_export->value);
		// printf("declare -x %s=\"%s\"\n", temp_export->key,
		// temp_export->value);
		temp_export = temp_export->next;
	}
	temp_export = export;
	while (temp_export != NULL)
	{
		next_export = temp_export->next;
		free(temp_export->key);
		free(temp_export->value);
		free(temp_export);
		temp_export = next_export;
	}
	get_control()->return_status = 0;
}

t_export	*create_new_export(t_hash_item *current_item)
{
	t_export	*new_export;

	new_export = ft_calloc(1, sizeof(t_export));
	new_export->key = ft_strdup(current_item->key);
	new_export->value = ft_strdup(current_item->value);
	new_export->next = NULL;
	return (new_export);
}

t_export	*insert_export(t_export *export_list, t_export *new_export)
{
	t_export	*prev_export;
	t_export	*temp_export;

	prev_export = NULL;
	temp_export = export_list;
	while (temp_export != NULL && ft_strcmp(temp_export->key,
			new_export->key) < 0)
	{
		prev_export = temp_export;
		temp_export = temp_export->next;
	}
	new_export->next = temp_export;
	if (prev_export == NULL)
		export_list = new_export;
	else
		prev_export->next = new_export;
	return (export_list);
}

void	print_export(t_hash_table *hash)
{
	t_hash_item	*current_item;
	t_export	*export_list;
	t_export	*new_export;
	int			i;

	export_list = NULL;
	i = 0;
	while (i < hash->size)
	{
		current_item = hash->item[i];
		while (current_item != NULL)
		{
			new_export = create_new_export(current_item);
			export_list = insert_export(export_list, new_export);
			current_item = current_item->next;
		}
		i++;
	}
	print_n_free(export_list);
}

void	hash_update_value(t_hash_table *hash, char *key)
{
	int		i;
	char	*equal_pos;
	int		key_length;

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

int	check_error(char *str, t_hash_table *hash)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n", str);
			get_control()->return_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	export(t_cmd *cmd, t_hash_table *hash)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	int		i;

	i = 1;
	if (ft_array_len(cmd->args) == 1)
		print_export(hash);
	else
	{
		while (cmd->args[i])
		{
			if (hash_search(hash, cmd->args[i]) != NULL)
				hash_update_value(hash, cmd->args[i]);
			else if (check_error(cmd->args[i], hash) == 1)
			{
				equal_pos = ft_strchr(cmd->args[i], '=');
				if (equal_pos == NULL)
				{
					key = ft_strdup(cmd->args[i]);
					value = ft_strdup("");
				}
				else
				{
					key = ft_substr(cmd->args[i], 0, equal_pos - cmd->args[i]);
					value = ft_strdup(equal_pos + 1);
					if (!value)
						value = ft_strdup("");
				}
				hash_insert(&hash, key, value);
				free(key);
				if (value)
					free(value);
				get_control()->return_status = 0;
			}
			i++;
		}
	}
	if (get_control()->cmd->on_fork == 1)
		exit(get_control()->return_status);
}
