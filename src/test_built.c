/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:48:30 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/28 16:25:06 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test_built(t_token *token, t_minishell *mini)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini->cmd != NULL)
	{
		if (mini->cmd->type == WORD && is_builtin(mini->cmd->name) < 0)
		{
			if (is_builtin(token->content) == PWD)
			{
				printf("\n=========================    PWD    =========================\n\n");
				ft_pwd(mini);
			}

			if (is_builtin(mini->cmd->name) == ECHO)
			{
				printf("\n=========================    ECHO    =========================\n\n");
				ft_echo(mini, mini->cmd);
			}
		}
		if (token->type == HEREDOC)
		{
			printf("\n=========================  HEREDOC  =========================\n\n");
			hand_heredoc(mini);
		}
		// if (token->type == OUTPUT)
		// {
		// 	printf("\n=========================  OUTPUT  =========================\n\n");
		// 	ft_redirect_out(mini);
		// }
	mini->cmd = mini->cmd->next;
	}
}