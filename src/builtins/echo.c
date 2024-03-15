/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:57:02 by  jaqribei         #+#    #+#             */
/*   Updated: 2024/03/15 20:57:31 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	n_flag;
	int	i;
	int	fd_out;

	i = 1;
	n_flag = 0;
	fd_out = 1;
	if (cmd->redirect_list_out)
		fd_out = cmd->redirect_list_out->fd_out;
	if (!cmd->args[i])
		ft_putstr_fd("\n", fd_out);
	while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(cmd->args[i], fd_out);
		if (cmd->args[i + 1] != NULL)
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", fd_out);
}
