/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:20:21 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/20 15:56:36 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*pwd;
	int		fd_out;

	fd_out = 1;
	if (cmd->on_fork == 0)
	{
		cmd->redirect_list_out = lstlast_out(cmd->redirect_list_out);
		if (cmd->redirect_list_out)
			fd_out = cmd->redirect_list_out->fd_out;
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_printf_fd(fd_out, "%s\n", pwd);
	else
	{
		ft_printf_fd(STDERR_FILENO, "minishell: pwd error\n");
		get_control()->return_status = 1;
	}
	get_control()->return_status = 0;
	free(pwd);
	if (cmd->on_fork == 1)
		free_n_exit_child(get_control());
}
