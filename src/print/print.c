/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:12:49 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/11 14:03:10 by eddos-sa         ###   ########.fr       */
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
	int		i;
	int		j;
	t_cmd	*aux;

	j = 0;
	aux = lst_first(cmd);
	while (aux)
	{
		i = 0;
		while (aux->args[i])
		{
			printf("Node: %d, Name: %s Arg: %d String: %s \n", j, aux->name, i,
				aux->args[i]);
			i++;
		}
		j++;
		aux = aux->next;
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
