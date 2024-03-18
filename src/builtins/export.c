/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:01:10 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/17 16:01:30 by jaqribei         ###   ########.fr       */
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

void	print_n_free(t_export *export, t_cmd *cmd)
{
	t_export	*temp_export;
	t_export	*next_export;
	int			fd_out;

	temp_export = export;
	fd_out = 1;
	cmd->redirect_list_out = lstlast_out(cmd->redirect_list_out);
	if (cmd->redirect_list_out)
		fd_out = cmd->redirect_list_out->fd_out;
	while (temp_export != NULL)
	{
		if (!ft_strncmp(temp_export->value, "", 1))
			ft_printf_fd(fd_out, "declare -x %s\n", temp_export->key);
		else
			ft_printf_fd(fd_out, "declare -x %s=\"%s\"\n", temp_export->key, \
			temp_export->value);
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
	while (temp_export != NULL && ft_strcmp(temp_export->key, \
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

void	print_export(t_hash_table *hash, t_cmd *cmd)
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
	print_n_free(export_list, cmd);
}
