/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:01 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/17 14:28:09 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_execution(t_cmd *cmd, t_minishell *mini)
{
	if (cmd->type == WORD)
	{
		if (is_builtin(cmd->name) == PWD)
			ft_pwd(cmd);
		else if (is_builtin(cmd->name) == ECHO)
			ft_echo(cmd);
		else if (is_builtin(cmd->name) == CD)
			hand_cd(cmd);
		else if (is_builtin(cmd->name) == ENV)
			env(cmd, &mini->table);
		else if (is_builtin(cmd->name) == EXPORT)
			export(cmd, mini->table);
		else if (is_builtin(cmd->name) == UNSET)
			unset(mini, cmd);
		else if (is_builtin(cmd->name) == EXIT)
			ft_exit(cmd, &mini->table);
	}
}
