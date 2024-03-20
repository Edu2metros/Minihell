/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:37:53 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 20:39:12 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	execute_without_path(t_cmd *cmd)
{
	if (is_directory(cmd->name))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n",
			cmd->name);
		exit(126);
	}
	if (access(cmd->name, F_OK | X_OK) == 0 && ft_strcmp(cmd->name, ".."))
		execve(cmd->name, cmd->args, get_control()->table->env);
	else
	{
		ft_printf_fd(STDERR_FILENO, "minishell: \
%s: No such file or directory\n", cmd->name);
		exit(127);
	}
}

void	single_command_child(t_cmd *cmd, t_minishell *mini)
{
	char	*path;

	if (cmd->return_status != 0)
	{
		free_all_child(mini);
		exit(cmd->return_status);
	}
	exec_redirect(cmd);
	if (cmd->name[0] == '.' || cmd->name[0] == '/')
		execute_without_path(cmd);
	path = get_path(mini, cmd->name);
	execve(path, cmd->args, mini->table->env);
}

void	exec_command(t_cmd *cmd, t_minishell *mini)
{
	pid_t	pid;
	t_cmd	*aux;
	int		i;
	int		status;

	aux = lst_first(cmd);
	i = 0;
	if (is_builtin(cmd->name) != 0)
	{
		builtin_execution(cmd, mini);
		return ;
	}
	pid = fork();
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, handle_sigquit_signal);
	if (pid == 0)
		single_command_child(cmd, mini);
	if (pid)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mini->return_status = WEXITSTATUS(status);
	}
	free_reds(aux);
}
