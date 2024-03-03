/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:01 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/03 03:16:24 by  jaqribei        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	test_built(t_token *token, t_minishell *mini)
{
	int	i;
	int	j;
	t_hash_table		*table;

	i = 0;
	j = 0;
	table = hash_population(mini, &table);
	
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
			if (is_builtin(mini->cmd->name) == ENV)
				env(mini->cmd, &table);
		}
		if (token->type == HEREDOC)
			hand_heredoc(mini);
		mini->cmd = mini->cmd->next;
	}
}
