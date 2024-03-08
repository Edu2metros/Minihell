#include "../include/minishell.h"

// Arrumar execução
// redirect in / heredoc
// memória
// pipe
// tratar FDs abertos

/* void	exec_pipe(t_minishell *mini)
{
	int		i;
	int		fd[2];
	pid_t	pid;
	t_cmd	*cmd;
	t_cmd	*aux;

	i = 0;
	cmd = mini->cmd;
	while (mini->pipe->pipe_count > 0)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			execution(cmd, mini);
			close(fd[1]);
			exit(0);
		}
		else
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			waitpid(pid, NULL, 0);
		}
		aux = cmd;
		cmd = cmd->next;
		mini->pipe->pipe_count--;
	}
} */


//1 write (in)
//0 read (out)

void	exec_pipe(t_minishell *mini)
{
	int	fd[2];
	pid_t pid;
	t_cmd *cmd;
	cmd = mini->cmd;

	while(mini->pipe->pipe_count > 0)
	{
		pipe(mini->pipe->fd);
		pid = fork();
		if(pid == 0)
		{
			close(mini->pipe->fd[0]);
			dup2(mini->pipe->fd[1], STDIN_FILENO);
			close(mini->pipe->fd[1]);
			execution(cmd, mini);
			kill(pid, SIGKILL);
		}
		else
		{
			close(mini->pipe->fd[1]);
			dup2(mini->pipe->fd[0], STDOUT_FILENO);
			close(mini->pipe->fd[0]);
			waitpid(pid, NULL, 0);
		}
		mini->pipe->pipe_count--;
		cmd = cmd->next;
	}
}

void execution(t_cmd *cmd, t_minishell *mini)
{
    char **path = ft_split(getenv("PATH"), ':');
    int i = 0;
    pid_t pid = fork();

    while (path[i] != NULL && pid == 0)
    {
        if (is_builtin(cmd->name) != 0)
            builtin_execution(mini->token, mini);

        char *tmp = ft_strjoin(path[i], "/");
        tmp = ft_strjoin(tmp, cmd->name);

        if (access(tmp, F_OK) == 0)
        {
            execve(tmp, cmd->args, NULL);
            break;
        }

        i++;
        free(tmp);
    }

    if (pid)
        waitpid(pid, NULL, 0);
}

