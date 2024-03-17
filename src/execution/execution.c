/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:11:32 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/17 14:04:01 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_redirect(t_cmd *cmd)
{
	if (cmd->redirect_list_in)
	{
		cmd->redirect_list_in = lstlast_in(cmd->redirect_list_in);
		dup2(cmd->redirect_list_in->fd_in, 0);
	}
	if (cmd->redirect_list_out)
	{
		cmd->redirect_list_out = lstlast_out(cmd->redirect_list_out);
		dup2(cmd->redirect_list_out->fd_out, 1);
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*get_path(t_minishell *mini, char *command)
{
	char	**path;
	char	*tmp;
	int		i;
	char	*full_path;

	i = 0;
	if (command == NULL)
		exit(127);
	path = ft_split(hash_search(mini->table, "PATH"), ':');
	if (path == NULL)
	{
		ft_printf_fd(STDERR_FILENO,
						"minishell: \
			%s: No such file or directory \n",
						command);
		exit(127);
	}
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, F_OK) == 0)
		{
			free_array(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", command);
	exit(127);
}

void	exec_pipe_command(t_cmd *cmd, t_minishell *mini)
{
	pid_t	pid;
	char	*path;
	int		i;

	i = 0;
	if (cmd->name[0] == '.' || cmd->name[0] == '/')
	{
		if (access(cmd->name, F_OK | X_OK) == 0)
			execve(cmd->name, cmd->args, mini->table->env);
	}
	path = get_path(mini, cmd->name);
	// exec_redirect(cmd);
	execve(path, cmd->args, mini->table->env);
	free(path);
}

void	exec_command(t_cmd *cmd, t_minishell *mini)
{
	pid_t	pid;
	char	*path;
	int		i;
	int		status;

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
	{
		if (cmd->name[0] == '.' || cmd->name[0] == '/')
		{
			if (access(cmd->name, F_OK | X_OK) == 0)
				execve(cmd->name, cmd->args, mini->table->env);
			else
			{
				ft_printf_fd(STDERR_FILENO, "minishell: \
					%s: No such file or directory\n", cmd->name);
				exit(127);
			}
		}
		path = get_path(mini, cmd->name);
		exec_redirect(cmd);
		execve(path, cmd->args, mini->table->env);
	}
	if (pid)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mini->return_status = WEXITSTATUS(status);
	}
}
