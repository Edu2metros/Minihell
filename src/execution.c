#include "../include/minishell.h"

// Arrumar execução
// redirect in / heredoc
// memória
// pipe
// tratar FDs abertos

void handle_pipe(char **first_arg, char **second_arg)
{
	// if(mini->redirect_list_out || mini->redirect_list_in)
	
}

void	minishell(t_minishell *mini)
{
	int i;
	i = 0;
	if (mini->pipe->pipe_count == 0)
		execution(mini->cmd, mini);
	else
	{
		while(mini->token)
		{
			handle_pipe(mini->cmd->args, mini->cmd->next->args);
						
		}
		
	}
}

void	execution(t_cmd *cmd, t_minishell *mini)
{
	char	**path;
	pid_t	pid;
	char	*tmp;
	int		i;

	path = ft_split(hash_search(mini->table, "PATH"), ':');
	// fazer uma validação se caso path == NULL;
	i = 0;
	pid = fork();
	while (path[i] != NULL && pid == 0)
	{
		if (is_builtin(cmd->name) != 0)
		{
			builtin_execution(mini->token, mini);
			exit(EXIT_SUCCESS);	
		}
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, cmd->name);
		if (access(tmp, F_OK) == 0)
		{
			if (mini->redirect_list_out)
			{
				mini->redirect_list_out = lstlast_out(mini->redirect_list_out);
				dup2(mini->redirect_list_out->fd_out, 1);
			}
			execve(tmp, cmd->args, NULL);
			break ;
		}
		i++;
		free(tmp);
	}
	if (pid)
		waitpid(pid, NULL, 0);
}
