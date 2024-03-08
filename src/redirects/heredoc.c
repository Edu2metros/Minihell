/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:56 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/07 19:53:19 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hand_heredoc(t_minishell *mini)
{
	t_token	*token;
	char	*delimiter;
	char	*input;
	int		fd;
	
	token = mini->token;
	while (token)
	{
		if (token->type == HEREDOC && (token->next->type == WORD || token->next->type == QUOTE))
		{
			delimiter = token->next->content;
			mini->cmd->fd = open("Heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (1)
			{
				input = readline(HEREDOC_PROMPT);
				if (!input || (ft_strcmp(input, delimiter) == 0))
				{
					free(input);
					close(mini->cmd->fd);
					unlink("Heredoc");
					break;
				}
				ft_putendl_fd(input, mini->cmd->fd);
				free(input);
			}
		}
		token = token->next;
	}
}