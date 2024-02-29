/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:01 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/29 16:04:58 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	test_built(t_token *token, t_minishell *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini->cmd != NULL)
	{
		if (mini->cmd->type == WORD)
		{
			if (is_builtin(mini->cmd->name) == PWD)
				ft_pwd();
			if (is_builtin(mini->cmd->name) == ECHO)
				ft_echo(mini->cmd);
			if (is_builtin(mini->cmd->name) == CD)
				hand_cd(mini->cmd);
		}
		if (token->type == HEREDOC)
			hand_heredoc(mini);
		mini->cmd = mini->cmd->next;
	}
}
