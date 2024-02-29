/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:56 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/29 15:01:16 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hand_heredoc(t_minishell *mini)
{
	t_token	*token;
	char	*input;
	int		fd;

	token = mini->token;
	while (token)
	{
		if (token->type == HEREDOC && token->next->type == WORD)
		{
			fd = open("Heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (1)
			{
				input = readline(">>>>> ");
				if (!input || !ft_strcmp(input, token->next->content))
					break ;
				ft_putendl_fd(input, fd);
				free(input);
			}
			free(input);
			close(fd);
			unlink("Heredoc");
		}
		token = token->next;
	}
}
