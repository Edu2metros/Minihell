/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:21:20 by  jaqribei         #+#    #+#             */
/*   Updated: 2024/03/20 15:54:37 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(t_cmd *cmd, t_hash_table **table)
{
	int	fd_out;

	fd_out = 1;
	if (cmd->on_fork == 0)
	{
		cmd->redirect_list_out = lstlast_out(cmd->redirect_list_out);
		if (cmd->redirect_list_out)
			fd_out = cmd->redirect_list_out->fd_out;
	}
	if (cmd->args[1] != NULL)
	{
		get_control()->return_status = 127;
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		return ;
	}
	else
		print_table(table, fd_out);
	if (cmd->redirect_list_out)
		close(fd_out);
	get_control()->return_status = EXIT_SUCCESS;
	if (cmd->on_fork == 1)
		free_n_exit_child(get_control());
}
