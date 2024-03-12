#include "../include/minishell.h"

void	exec_redirect(t_cmd *cmd)
{
	if (cmd->redirect_list_in)
		dup2(cmd->redirect_list_in->fd_in, 0);
	if (cmd->redirect_list_out)
	{
		cmd->redirect_list_out = lstlast_out(cmd->redirect_list_out);
		dup2(cmd->redirect_list_out->fd_out, 1);
	}
}

char	*get_path(t_minishell *mini, char *command)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	path = ft_split(hash_search(mini->table, "PATH"), ':');
	if (path == NULL)
	{
		ft_putstr_fd("Command not found.", 2);
		return (NULL);
	}
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, command);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		i++;
	}
	return (NULL);
}

void	simple_execution(t_cmd *cmd, t_minishell *mini)
{
	pid_t	pid;
	char	*path;
	int		i;

	i = 0;
	pid = fork();
	path = get_path(mini, cmd->name);
	if (pid == 0)
	{
		if (is_builtin(cmd->name) != 0)
		{
			// exec_redirect(cmd);
			builtin_execution(mini->token, mini);
			exit(EXIT_SUCCESS);
		}
		exec_redirect(cmd);
		execve(path, cmd->args, NULL);
		free(path);
	}
	if (pid)
		waitpid(pid, NULL, 0);
}
