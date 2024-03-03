/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:21:20 by  jaqribei         #+#    #+#             */
/*   Updated: 2024/03/03 14:25:18 by  jaqribei        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(t_cmd *cmd, t_hash_table **table)
{
	if (cmd->args[1] != NULL) // env does not have any arguments
	{
		// get_control()->code_error - 127;
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		return ;
	}
	else
		print_table(table);	
	free_table(table);
}
