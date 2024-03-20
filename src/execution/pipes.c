/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:31:35 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/20 10:41:27 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fd_redirections(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	handle_input_redirection(t_cmd *cmd)
{
	if (cmd->redirect_list_in)
	{
		cmd->redirect_list_in = lstlast_in(cmd->redirect_list_in);
		dup2(cmd->redirect_list_in->fd_in, STDIN_FILENO);
		close(cmd->redirect_list_in->fd_in);
	}
}

void	handle_output_redirection(t_cmd *cmd, int fd_in, int fd_out)
{
	if (cmd->redirect_list_out)
	{
		cmd->redirect_list_out = lstlast_out(cmd->redirect_list_out);
		fd_redirections(fd_in, cmd->redirect_list_out->fd_out);
	}
	else
		fd_redirections(fd_in, fd_out);
}

void	handle_child_process(t_cmd *cmd, t_minishell *mini, int fd[], int fd_in)
{
	close(fd[0]);
	handle_input_redirection(cmd);
	if (cmd->next)
		handle_output_redirection(cmd, fd_in, fd[1]);
	else
		handle_output_redirection(cmd, fd_in, STDOUT_FILENO);
	cmd->on_fork = is_builtin(cmd->name);
	if (is_builtin(cmd->name))
	{
		cmd->on_fork = 1;
		builtin_execution(cmd, mini);
	}
	else
		exec_pipe_command(cmd, mini);
	exit(EXIT_SUCCESS);
}
