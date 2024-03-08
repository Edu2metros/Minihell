/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:01 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/07 20:00:18 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_execution(t_token *token, t_minishell *mini)
{
	if (mini->cmd->type == WORD)
	{
		if (is_builtin(mini->cmd->name) == PWD)
			ft_pwd();
		else if (is_builtin(mini->cmd->name) == ECHO)
			ft_echo(mini->cmd);
		else if (is_builtin(mini->cmd->name) == CD)
			hand_cd(mini->cmd);
		else if (is_builtin(mini->cmd->name) == ENV)
			env(mini->cmd, &mini->table);
		else if (is_builtin(mini->cmd->name) == EXPORT)
			export(mini->cmd, mini->table);
		else if (is_builtin(mini->cmd->name) == UNSET)
			unset(mini, mini->cmd);
		else if (is_builtin(mini->cmd->name) == EXIT)
			ft_exit(mini->cmd, mini->cmd->args[1]);
	}
}
