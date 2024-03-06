/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:56 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/06 20:10:46 by eddos-sa         ###   ########.fr       */
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
		if (token->type == HEREDOC && token->next->type == WORD)
		{
			delimiter = token->next->content;
			mini->redirect_list_in->fd_in = open("Heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (1)
			{
				input = readline(">> ");
				if (!input || (ft_strcmp(input, delimiter) == 0))
				{
					free(input);
					close(mini->redirect_list_in->fd_in);
					unlink("Heredoc");
					break;
				}
				ft_putendl_fd(input, mini->redirect_list_in->fd_in);
				free(input);
			}
		}
		token = token->next;
	}
}