#include "../include/minishell.h"

void	fd_redirections(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	exec_pipe(t_minishell *mini, t_cmd *cmd)
{
	int		fd[2];
	int		fd_in;
	pid_t	pid;

	fd_in = STDIN_FILENO;
	while (cmd)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			close(fd[0]);
			if (cmd->next != NULL)
				fd_redirections(STDIN_FILENO, fd[1]);
			else
				fd_redirections(fd_in, STDOUT_FILENO);
			if (is_builtin(cmd->name))
				builtin_execution(cmd, mini);
			else
				exec_pipe_command(cmd, mini);
			exit(EXIT_SUCCESS);
		}
		else
			close(fd[1]);
		fd_in = fd[0];
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
	// waitpid(-1, NULL, 0);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
}

/* void	exec_pipe(t_minishell *mini, t_cmd *cmd)
{
	int		fd[2];
	int		fd_in;
	pid_t	pid;

	fd_in = STDIN_FILENO;
	while (cmd)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (cmd->next != NULL)
				fd_redirections(fd_in, fd[1]);
			else
				fd_redirections(fd_in, STDOUT_FILENO);
			if (is_builtin(cmd->name))
				builtin_execution(cmd, mini);
			else
				exec_pipe_command(cmd, mini);
			exit(0); // Kill the built-in process
		}
		else
		{
			wait(NULL);
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			close(fd[1]);
			fd_in = fd[0];
			cmd = cmd->next;
		}
	}
} */