/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:11:32 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 14:05:22 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_redirect(t_cmd *cmd)
{
	if (cmd->redirect_list_in)
	{
		cmd->redirect_list_in = lstlast_in(cmd->redirect_list_in);
		dup2(cmd->redirect_list_in->fd_in, STDIN_FILENO);
	}
	if (cmd->redirect_list_out)
	{
		cmd->redirect_list_out = lstlast_out(cmd->redirect_list_out);
		dup2(cmd->redirect_list_out->fd_out, STDOUT_FILENO);
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

void	free_all_child(t_minishell *mini)
{
	free_all(mini);
	clear_history();
	free_table(&mini->table);
}

char	*get_path(t_minishell *mini, char *command)
{
	char	**path;
	char	*tmp;
	int		i;
	char	*full_path;
	char	*path_value;

	i = 0;
	if (command == NULL)
		exit(127);
	path_value = hash_search(mini->table, "PATH");
	if (path_value == NULL)
	{
		ft_printf_fd(STDERR_FILENO,
						"minishell: %s: No such file or directory \
        n",
						command);
		exit(127);
	}
	path = ft_split(path_value, ':');
	free(path_value);
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
	free_array(path);
	free_all_child(mini);
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
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, handle_sigquit_signal);
	execve(path, cmd->args, mini->table->env);
	free(path);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
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
		if (cmd->return_status != 0)
		{
			free_all_child(mini);
			exit(cmd->return_status);
		}
		if (cmd->name[0] == '.' || cmd->name[0] == '/')
		{
			if (is_directory(cmd->name))
			{
				ft_printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", \
				cmd->name);
				exit(126);
			}
			if (access(cmd->name, F_OK | X_OK) == 0 && ft_strcmp(cmd->name,
					".."))
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
