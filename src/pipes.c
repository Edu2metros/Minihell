#include "../include/minishell.h"
#include "minishell.h" // Certifique-se de incluir o cabeçalho apropriado aqui
#include <stdlib.h>
#include <unistd.h>

void	pipe_execution(t_minishell *mini, int fd_in)
{
	char	**path;
	char	*tmp;
	pid_t	pid;
	int		i;

	i = 0;
	pipe(mini->pipe->fd);
	pid = fork();
	path = ft_split(hash_search(mini->table, "PATH"), ':');
	if (pid == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		if (mini->pipe->pipe_count > 0)
			dup2(mini->pipe->fd[1], STDOUT_FILENO);
			close(fd_in);
		while (path[i] != NULL)
		{
			tmp = ft_strjoin(path[i], "/");
			tmp = ft_strjoin(tmp, mini->cmd->name);
			if (access(tmp, X_OK) == 0)
				execve(tmp, mini->cmd->args, NULL);
			i++;
			free(tmp);
		}
	}
}

void	pipes(t_minishell *mini)
{
	int fd_in;
	int i;
	fd_in = dup(STDIN_FILENO);
	while (mini->pipe->pipe_count >= 0)
	{
		if (mini->cmd->type == WORD)
			pipe_execution(mini, fd_in);
		mini->pipe->pipe_count--;
	}
}