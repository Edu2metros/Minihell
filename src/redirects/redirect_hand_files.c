/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_hand_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:29:10 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 20:47:01 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_out_files(t_redirect_out *redirect, t_cmd *cmd)
{
	char	*file;

	file = redirect->content;
	if (redirect->type == OUTPUT)
	{
		redirect->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (redirect->fd_out == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: \
%s: No such file or directory\n", file);
			cmd->return_status = 1;
			return ;
		}
	}
	else if (redirect->type == APPEND)
	{
		redirect->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redirect->fd_out == -1)
		{
			if (cmd->return_status != 1)
				ft_printf_fd(STDERR_FILENO, "minishell: \
%s: No such file or directory\n", file);
			cmd->return_status = 1;
			return ;
		}
	}
}

void	handle_in_files(t_redirect_in *redirect, t_cmd *cmd)
{
	char	*file;

	if (redirect->type == HEREDOC)
	{
		redirect->heredoc = 1;
		redirect->fd_in = open("heredoc", O_RDONLY);
	}
	if (redirect->type == INPUT)
	{
		file = redirect->content;
		redirect->heredoc = 0;
		redirect->fd_in = open(file, O_RDONLY);
		if (redirect->fd_in == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: \
%s: No such file or directory\n", file);
			cmd->return_status = 1;
			return ;
		}
	}
}
