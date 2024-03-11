#include "../include/minishell.h"

void	execution_pipe(t_cmd *cmd_list, int fd[2])
{
	char	**path;
	int		i;
	char	*tmp;

	path = ft_split(hash_search(get_control()->table, "PATH"), ':');
	// fazer a verificação se caso path == NULL
	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, cmd_list->name);
		if (execve(tmp, cmd_list->args, NULL) != -1)
			break ;
		free(tmp);
		i++;
	}
}

void	ft_putstring_fd(int fd)
{
	int	c;

	while (read(fd, &c, 1) != -1)
		write(2, &c, 1);
}

void	pipes(t_minishell *mini)
{
	int		new_pipe[2];
	pid_t	pid;
	t_cmd	*aux;
	pid_t	pid2;

	aux = lst_first(mini->cmd);
	pipe(new_pipe);
	pid = fork();
	if (pid == 0)
	{
		dup2(new_pipe[1], STDOUT_FILENO);
		close(new_pipe[0]);
		close(new_pipe[1]);
		execution_pipe(aux, new_pipe);
		exit(0);
	}
	else
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(new_pipe[0], STDIN_FILENO);
			close(new_pipe[0]);
			close(new_pipe[1]);
			execution_pipe(aux->next->next, new_pipe);
			exit(0);
		}
	}
	close(new_pipe[0]);
	close(new_pipe[1]);
	waitpid(pid2, NULL, 0);
}
