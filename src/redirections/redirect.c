/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:12:19 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/21 22:42:14 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_redirect_in(t_minishell *mini)
// {
// 	t_token	*token;
// 	char	*infile;
// 	int		fd;
	
// 	token = mini->token;
// 	while (token)
// 	{
// 		if (token->type == INPUT && token->next->type == WORD)
// 		{
// 			infile = token->next->content;
// 			fd = open(infile, O_RDONLY);
// 			if (fd < 0)
// 				return (EXIT_FAILURE);
// 			dup2()
			
// 		}
// 		token = token->next;
// 	}
// }

void	ft_redirect_out(t_minishell *mini)
{
	t_token	*token;
	char	*outfile;
	int		fd;
	
	token = mini->token;
	while (token)
	{
		if (token->type == OUTPUT && token->next->type == WORD)
		{
			outfile = token->next->content;
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				exit(EXIT_FAILURE);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		token = token->next;
	}
}
