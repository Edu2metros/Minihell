#include "../../include/minishell.h"

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
	if (cmd->next != NULL && !cmd->redirect_list_out)
	{
		fd_redirections(STDIN_FILENO, fd[1]);
		fd_redirections(fd_in, STDOUT_FILENO);
	}
	else if (cmd->next != NULL && cmd->redirect_list_out)
	{
		cmd->redirect_list_out = lstlast_out(cmd->redirect_list_out);
		fd_redirections(STDIN_FILENO, fd[1]);
		fd_redirections(fd_in, cmd->redirect_list_out->fd_out);
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

void	exec_pipe(t_minishell *mini, t_cmd *cmd)
{
	int		fd[2];
	int		fd_in;
	int		count;
	pid_t	pid;

	if (cmd->redirect_list_in)
	{
		cmd->redirect_list_in = lstlast_in(cmd->redirect_list_in);
		dup2(cmd->redirect_list_in->fd_in, STDIN_FILENO);
	}
	fd_in = STDIN_FILENO;
	count = lstsize_cmd(cmd);
	while (cmd)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: fork error\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			handle_child_process(cmd, mini, fd, fd_in);
		else
			handle_parent_process(&cmd, fd, &fd_in);
	}
	close(fd[0]);
	while(waitpid(-1, NULL, 0) > 0 && count > 0)
		count--;
}
