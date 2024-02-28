/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:57:02 by  jaqribei         #+#    #+#             */
/*   Updated: 2024/02/28 20:11:06 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// mimics the behavior of the echo command in a Unix shell.
// Need to make the command list and rewiew the implementation of the echo command

void	ft_echo(t_minishell *mini, t_cmd *cmd)
{
	int	n_flag;
	int	i;

	i = 1;
	cmd = lst_first(cmd);
	n_flag = 0;
	if (!cmd->args[i])
		ft_putstr_fd("\n", 1);
	while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", 1);
}

//need to check the quote stuff, to not print quotes and do not ignore spaces