/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:56 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/17 15:58:47 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_heredoc_child_process(t_minishell *mini)
{
	if (mini->token != NULL)
		free_tokens(&mini->token);
	// if (get_control()->cmd != NULL)
	// free_cmd(&get_control()->cmd);
	rl_clear_history();
	close_fd(get_control());
	exit(0);
}

void	get_heredoc(void)
{
	int		fd;
	char	*delimiter;
	t_token	*token;

	token = get_control()->token;
	while (token)
	{
		if (token->type == HEREDOC && (token->next->type == WORD || token->next->type == QUOTE))
		{
			fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			delimiter = token->next->content;
			if (!get_control()->heredoc)
				heredoc_child_process(delimiter, fd);
		}
		token = token->next;
	}
}

void	heredoc_child_process(char *delimiter, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
		hand_heredoc(delimiter, fd);
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

void	hand_heredoc(char *delimiter, int fd)
{

	char	*input;
	while (1)
	{
		input = readline(HEREDOC_PROMPT);
		if (!input)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted `%s\')", delimiter);
			free(input);
			break;
		}
		else if ((ft_strcmp(input, delimiter) == 0))
		{
			free(input);
			break;
		}
		// if (ft_strcmp(input, "$"))
		// 	input = expand_variable(get_control()->token);
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
	clear_heredoc_child_process(get_control());
}
