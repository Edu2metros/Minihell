/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:02:27 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/29 15:48:16 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_cmd_list(t_minishell *mini)
{
	t_token	*token;
	int		count;

	token = mini->token;
	count = 0;
	while (token)
	{
		if (token->type == WORD && !count)
		{
			count = 1;
			mini->cmd = add_new_node(mini->cmd, (mini->token)->content,
					(mini->token)->type);
			populate_cmd_args(&token, mini->cmd);
		}
		else
		{
			count = 0;
			token = token->next;
		}
	}
	free_tokens(&token);
}

t_cmd	*lst_first(t_cmd *cmd)
{
	t_cmd	*result;

	result = cmd;
	while (result != NULL && result->previous != NULL)
		result = result->previous;
	return (result);
}
