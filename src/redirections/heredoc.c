/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:56 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/21 18:47:11 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_heredoc(t_minishell *mini)
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
			fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (1)
			{
				input = readline("> ");
				if (!input || !(ft_strcmp(input, delimiter)))
				{
					free(input);
					close(fd);
					break ;
				}
				ft_putendl_fd(input, fd);
				free(input);
			}
		}
		token = token->next;
	}
}
