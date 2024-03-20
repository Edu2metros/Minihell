/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:07:05 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 21:07:19 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_export(t_export *temp_export)
{
	t_export	*next_export;

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
