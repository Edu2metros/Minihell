/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/20 20:17:20 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_redirect(t_minishell *mini)
{
	int	type;
	
	type = mini->token->type;
	if (type == OUTPUT || type == INPUT || type == APPEND || type == HEREDOC)
		return (type);
	return (0);
}

t_cmd	*cmd_new_node(char *content, int type)
{
	t_cmd *cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if(!cmd)
		return (NULL);
	cmd->name = ft_strdup(content);
	cmd->type = type;
	cmd->args = NULL;
	cmd->count = 0;
	cmd->redirect[0] = 0;
	cmd->redirect[1] = 0;
	cmd->fd[0] = 0;
	cmd->fd[1] = 1;
	cmd->output = NULL;
	cmd->input = NULL;
	cmd->next = NULL;
	cmd->previous = NULL;
	return (cmd);
}

// void	add_cmd(t_cmd *cmd)
void	add_cmd_to_mini(t_minishell *mini, t_cmd *cmd)
{
	t_cmd	*aux;

	aux = cmd;
	// print_cmd_args(cmd);
	if (!aux)
	{
		aux = cmd;
		return ;
	}
	while (aux->next)
		aux = aux->next;
	aux->next = cmd;
	aux->next->previous = aux;
}

int	token_list_size(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		// if (token->type == WORD && token->previous && token->previous->type != is_redirect(mini))
		// 	count++;
		// token = token->next;
			if (token->type == WORD && token->previous && token->previous->type != INPUT
			&& token->previous->type != OUTPUT && token->previous->type != APPEND
			&& token->previous->type != HEREDOC)
			count++;
		token = token->next;
	}
	return (count);
}

void	populate_cmd_args(t_minishell *mini, t_token *token, t_cmd *cmd)
{
	// cmd->args = ft_calloc((token_list_size(token)), sizeof(char *));
	cmd->args = ft_calloc(500, sizeof(char *));
	if (!cmd->args)
		return ;
	cmd->args[cmd->count] = ft_strdup(token->content);
	cmd->count++;
	token = token->next;
	while (token && token->type != PIPE)
	{
		if (token && ft_strcmp(token->content, "") == 0)
		{
			token = token->next;
			continue ;
		}
		if (token->type == WORD && token->previous && token->previous->type != is_redirect(mini))
		{
			cmd->args[cmd->count] = ft_strdup(token->content);
			cmd->count++;
		}
		token = token->next;
	}
	cmd->args[cmd->count] = NULL;
}

void	add_cmd(t_minishell *mini, t_token **token, t_cmd **cmd, int *count)
{
	*count = 1;
	*cmd = cmd_new_node((mini->token)->content, (mini->token)->type);
	populate_cmd_args(mini, *token, *cmd);
	print_cmd_args(*cmd);
	add_cmd_to_mini(mini, *cmd);
}

void	create_cmd_list(t_minishell *mini)
{
	t_token	*token;
	t_cmd	*cmd = NULL;
	int		count;
	
	token = mini->token;
	count = 0;
	while (token)
	{
		if (token->type == WORD && !count)
			add_cmd(mini, &token, &cmd, &count);
		else
			token = token->next;
	}
}