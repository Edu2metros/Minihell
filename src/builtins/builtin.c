/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:01 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 20:46:24 by eddos-sa         ###   ########.fr       */
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

int	is_builtin(char *input)
{
	if (input == NULL)
		return (0);
	if (ft_strcmp(input, "cd") == 0)
		return (CD);
	else if (ft_strcmp(input, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(input, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(input, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(input, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(input, "env") == 0)
		return (ENV);
	else if (ft_strcmp(input, "exit") == 0)
		return (EXIT);
	else
		return (0);
}
