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

void	handle_child_process(t_cmd *cmd, t_minishell *mini, int fd[], int fd_in)
{
	close(fd[0]);
	if (cmd->next != NULL)
	{
		fd_redirections(STDIN_FILENO, fd[1]);
		fd_redirections(fd_in, STDOUT_FILENO);
	}
	else
		fd_redirections(fd_in, STDOUT_FILENO);
	if (is_builtin(cmd->name))
		builtin_execution(cmd, mini);
	else
		exec_pipe_command(cmd, mini);
	exit(EXIT_SUCCESS);
}

void	handle_parent_process(t_cmd **cmd, int fd[], int *fd_in)
{
	close(fd[1]);
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	*fd_in = fd[0];
	*cmd = (*cmd)->next;
}

int	lstsize_cmd(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	count_open_fds(void)
{
	int	count;
	int	max_fd;
	int	fd;

	count = 0;
	max_fd = sysconf(_SC_OPEN_MAX);
	if (max_fd == -1)
	{
		perror("sysconf");
		return ;
	}
	fd = 0;
	while (fd < max_fd)
	{
		if (fcntl(fd, F_GETFD) != -1)
			count++;
		fd++;
	}
	printf("FDs abertos: %d\n", count);
}

void	exec_pipe(t_minishell *mini, t_cmd *cmd)
{
	int		fd[2];
	int		fd_in;
	int		count;
	pid_t	pid;
	pid_t	terminated_pid;

	fd_in = STDIN_FILENO;
	count = lstsize_cmd(cmd);
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
			handle_child_process(cmd, mini, fd, fd_in);
		else
			handle_parent_process(&cmd, fd, &fd_in);
	}
	close(fd[0]);
	while (count > 0)
	{
		terminated_pid = waitpid(-1, NULL, WNOHANG);
		if (terminated_pid > 0)
		{
			printf("Processo filho %d terminou.\n", terminated_pid);
			count--;
		}
		else if (terminated_pid == -1)
		{
			perror("waitpid");
			break ;
		}
	}
	count_open_fds();
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