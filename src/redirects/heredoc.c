/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:56 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/20 01:45:58 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_heredoc_child_process(t_minishell *mini)
{
	close_fd();
	free_all_child(mini);
	exit(0);
}

void	get_heredoc(t_cmd *cmd, t_redirect_in *red)
{
	int		fd;
	char	*delimiter;
	t_token	*token;

	token = get_control()->token;
	while (token)
	{
		if (token->type == HEREDOC && (token->next->type == WORD
				|| token->next->type == QUOTE))
		{
			fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			delimiter = token->next->content;
			if (!get_control()->heredoc)
				heredoc_child_process(delimiter, fd, red);
		}
		token = token->next;
	}
	if (cmd->redirect_list_in)
		cmd->redirect_list_in->fd_in = open("heredoc", O_RDONLY);
}

void	heredoc_child_process(char *delimiter, int fd, t_redirect_in *red)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
		hand_heredoc(delimiter, fd, red);
	}
	else
		wait_heredoc(pid);
}

void	wait_heredoc(pid_t pid)
{
	int	status;
	int	status_addr;

	waitpid(pid, &status_addr, 0);
	if (WIFEXITED(status_addr))
	{
		status = WEXITSTATUS(status_addr);
		if (status == 130)
		{
			if (get_control()->return_status != 130)
				get_control()->heredoc = 1;
			get_control()->return_status = status;
		}
		else
			get_control()->return_status = EXIT_SUCCESS;
	}
}

void	free_node(t_redirect_in *red)
{
	t_redirect_in	*tmp;

	while (red)
	{
		tmp = red->next;
		free(red);
		red = tmp;
	}
}
