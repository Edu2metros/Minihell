/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:56 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/12 21:29:47 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void clear_heredoc_pid()
{
    if (get_control()->token != NULL)
        free_tokens(&get_control()->token);
    if (get_control()->table != NULL)
        free_table(&get_control()->table);
    rl_clear_history();
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    exit(get_control()->return_status);
}

void get_heredoc(void)
{
	t_token *token;
	char *delimiter;
	char *delimiter_expand;
	int fd;

	sig_ignore();
	token = get_control()->token;
	while (token)
	{
		if (token->type == HEREDOC && (token->next->type == WORD || token->next->type == QUOTE))
		{
			fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			delimiter = token->next->content;
			// if (token->next->type == WORD)
			// 	delimiter_expand = token->next->content;
			// else if (token->next->type == QUOTE)
			// 	delimiter = token->next->content;
			if (!get_control()->heredoc)
				heredoc_pid(delimiter, fd);
		}
		token = token->next;
	}
}

void heredoc_pid(char *delimiter, int fd)
{
	pid_t pid;
	t_hash_table *table;
	int status;
	int status_addr;

	table = get_control()->table;
	pid = fork();
	if (pid == 0)
	{
		sigint_handler(SIGINT);
		sigquit_handler(SIGQUIT);
		hand_heredoc(delimiter, fd);
	}
	else
	{
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
}

void hand_heredoc(char *delimiter, int fd)
{

	char *input;
	while (1)
	{
		input = readline(HEREDOC_PROMPT);
		if (!input)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted `%s\')", delimiter);
			free(input);
			exit(EXIT_FAILURE);
		}
		else if ((ft_strcmp(input, delimiter) == 0))
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		// if (ft_strcmp(input, "$") && delimiter == get_control()->token->next->type == QUOTE)
		// 	hand_heredoc_expand();
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
	clear_heredoc_pid();
}

// void hand_heredoc_expand(t_minishell *mini)
// {
// 	t_token *token;
// 	char *delimiter;
// 	char *input;
// 	int fd;

// 	token = mini->token;
// 	while (token)
// 	{
// 		if (token->type == HEREDOC && (token->next->type == WORD))
// 		{
// 			delimiter = token->next->content;
// 			// mini->cmd->fd = open("Heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			while (1)
// 			{
// 				input = readline(HEREDOC_PROMPT);
// 				if (!input || (ft_strcmp(input, delimiter) == 0))
// 				{
// 					free(input);
// 					// close(mini->cmd->fd);
// 					unlink("Heredoc");
// 					break;
// 				}
// 				// ft_putendl_fd(input, mini->cmd->fd);
// 				free(input);
// 			}
// 		}
// 		token = token->next;
// 	}
// }