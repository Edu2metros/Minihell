/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:20:30 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/20 15:59:16 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all_redirect_in(t_redirect_in *red, t_minishell *mini)
{
	free_node(red);
	free_tokens(&(mini->token));
	lstclear_cmd(&(mini->cmd));
	free_redirect_out(&(mini->redirect_list_out));
	free_redirect_in(&(red));
	close_fd();
	clear_history();
	free_table(&mini->table);
}

void	print_ctrld(char *delimiter)
{
	ft_printf_fd(STDERR_FILENO, "minishell: warning: here-document \
delimited by end-of-file (wanted `%s\')\n", delimiter);
}

void	hand_heredoc(char *delimiter, int fd, t_redirect_in *red)
{
	char	*input;

	while (1)
	{
		input = readline(HEREDOC_PROMPT);
		if (!input)
		{
			print_ctrld(delimiter);
			free(input);
			break ;
		}
		else if ((ft_strcmp(input, delimiter) == 0))
		{
			free(input);
			break ;
		}
		if (ft_strcmp(input, "$"))
			input = expand_variable_word(input, get_control());
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
	free_all_redirect_in(red, get_control());
	exit(0);
}
