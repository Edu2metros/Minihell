/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:12:49 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/03 17:40:31 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tokens(t_minishell *mini)
{
	t_token	*current_token;

	current_token = mini->token;
	while (current_token != NULL)
	{
		printf("Token: %s: Type: %d\n\n", current_token->content,
			current_token->type);
		current_token = current_token->next;
	}
}

void	print_cmd_args(t_cmd *cmd)
{
	int	i;

	if (cmd->args == NULL)
	{
		printf("No arguments.\n");
		return ;
	}
	while (cmd)
	{
		i = 0;
		while (cmd->args[i] != NULL)
		{
			printf("Argument %d: %s\n", i, cmd->args[i]);
			i++;
		}
		cmd = cmd->next;
	}
}

void	print_cmd_list(t_minishell *mini)
{
	int		i;
	t_cmd	*cmd;

	cmd = mini->cmd;
	i = 0;
	while (cmd)
	{
		while (i < cmd->count)
		{
			printf("%s ", cmd->args[i]);
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
}
