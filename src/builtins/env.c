/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:31:41 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/03 01:16:07 by  jaqribei        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(t_cmd *cmd, t_hash_table **table)
{
	if (cmd->args[1] != NULL) // env does not have any arguments
	{
		// get_control()->code_erro;
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		return ;
	}
	else
		print_table(table);	
}
