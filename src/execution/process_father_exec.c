/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_father_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:41:00 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/20 13:47:47 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_parent_process(t_cmd **cmd, int fd[], int *fd_in)
{
	close(fd[1]);
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	*fd_in = fd[0];
	*cmd = (*cmd)->next;
}

void	wait_processes(t_minishell *mini, t_cmd *aux, int count)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0 && count > 0)
	{
		if (WIFEXITED(status))
			mini->return_status = WEXITSTATUS(status);
		count--;
	}
	free_reds(aux);
}

void	fork_processes(t_minishell *mini, t_cmd *cmd, int fd_in)
{
	t_cmd	*aux;
	int		fd[2];
	int		count;
	pid_t	pid;

	aux = lst_first(cmd);
	count = lstsize_cmd(cmd);
	while (cmd)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (cmd->return_status != 0)
			{
				free_all_child(mini);
				exit(cmd->return_status);
			}
			handle_child_process(cmd, mini, fd, fd_in);
		}
		else
			handle_parent_process(&cmd, fd, &fd_in);
	}
	close(fd[0]);
	wait_processes(mini, aux, count);
}

void	exec_pipe(t_minishell *mini, t_cmd *cmd)
{
	int	fd_in;

	fd_in = STDIN_FILENO;
	setup_signals();
	fork_processes(mini, cmd, fd_in);
}
