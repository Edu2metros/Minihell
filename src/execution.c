#include "../include/minishell.h"

// Arrumar execução
// redirect in / heredoc
// memória
// pipe
// tratar FDs abertos

void	execution(t_cmd *cmd, t_minishell *mini)
{
	char	**path;
	char	*tmp;
	int		i;
	pid_t	pid;
	t_redirect_out *aux;

	path = ft_split(getenv("PATH"), ':');
	i = 0;
	pid = fork();
	// if(mini->pipe->pipe_count > 0)
		// exec_pipe(mini);
	while (path[i] != NULL && !pid)
	{
		if(is_builtin(cmd->name) != 0)
			builtin_execution(mini->token, mini);
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, cmd->name);
		if (access(tmp, F_OK) == 0)
		{
			if (mini->redirect_list_out->fd_out)
			{
				aux = lstlast_out(mini->redirect_list_out);
				printf("%i\n", dup2(aux->fd_out, STDOUT_FILENO));
			}
			if (mini->redirect_list_in->fd_in)
				printf("%i\n", dup2(mini->redirect_list_in->fd_in, STDIN_FILENO));
			execve(tmp, cmd->args, NULL);
			break ;
		}
		i++;
		free(tmp);
	}
	if (pid)
		waitpid(pid, NULL, 0);
	// kill(pid, SIGKILL);
}
