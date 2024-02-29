/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:31:41 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/29 16:35:39 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(t_cmd *cmd)
{
	int	i;

	get_control()->env = __environ;
	if (!cmd->args[i])
	{
		i = 0;
		while (get_control()->env[i])
		{
			if(strchr(get_control()->env[i], '='))
				printf("%s\n", get_control()->env[i]);
		}
		i++;
	}
	else
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
	
}
