/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:11:20 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 20:34:15 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipe_or_not(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = lst_first(mini->cmd);
	if (cmd == NULL || (cmd->next == NULL && cmd->name == NULL))
		return ;
	if (cmd->next == NULL)
		exec_command(cmd, mini);
	else
		exec_pipe(mini, cmd);
}
