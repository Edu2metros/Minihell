/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/28 14:43:00 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redirect(t_minishell *mini)
{
	int	type;

	type = mini->token->type;
	if (type == OUTPUT || type == INPUT || type == APPEND || type == HEREDOC)
		return (type);
	return (0);
}

t_cmd	*add_new_node(t_cmd *cmd, char *content, int type)
{
	t_cmd	*new;

	if (!cmd)
		return (cmd_new_node(content, type));
	new = NULL;
	new = cmd_new_node(content, type);
	new->previous = cmd;
	cmd->next = new;
	return (new);
}
t_cmd	*cmd_new_node(char *content, int type)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(cmd));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(content);
	cmd->type = type;
	cmd->args = NULL;
	cmd->count = 0;
	cmd->next = NULL;
	cmd->previous = NULL;
	return (cmd);
}

int	lstsize_pipe(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if(token->type == PIPE)
			return(i);
		i++;
		token = token->next;
	}
	return(i);
}

void	populate_cmd_args(t_minishell *mini, t_token **token, t_cmd *cmd)
{
	cmd->args = ft_calloc(lstsize_pipe(*token), sizeof(char *));
	if (!cmd->args)
		return ;
	cmd->args[cmd->count] = ft_strdup((*token)->content);
	cmd->count++;
	*token = (*token)->next;
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == WORD)
		{
			cmd->args[cmd->count] = ft_strdup((*token)->content);
			cmd->count++;
		}
		*token = (*token)->next;
	}
	cmd->count = 0;
}

void	add_cmd(t_minishell *mini, t_token **token, t_cmd **cmd, int *count)
{
	*count = 1;
	*cmd = add_new_node(*cmd, (mini->token)->content, (mini->token)->type);
	populate_cmd_args(mini, token, *cmd);
}

void	create_cmd_list(t_minishell *mini)
{
	t_token	*token;
	int		count;

	token = mini->token;
	count = 0;
	while (token)
	{
		if (token->type == WORD && !count)
			add_cmd(mini, &token, &mini->cmd, &count);
		else
		{
			count = 0;
			token = token->next;
		}
	}
	lstclear_token(&token);
}

t_cmd	*lst_first(t_cmd *cmd)
{
	t_cmd	*result;

	result = cmd;
	while (result != NULL && result->previous != NULL)
		result = result->previous;
	return (result);
}
