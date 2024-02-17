/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/17 19:40:41 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Set up Table of commands

//reads token list 
//breaks a pipeline into commands
//A pipeline is a list of commands separated by |
//A command comprises both the command name/path, its flags and associates redirections.

int is_redirect(t_minishell *mini)
{
	int	type;
	
	type = mini->token->type;
	if (type == OUTPUT || type == INPUT || type == APPEND || type == HEREDOC)
		return (type);
	return (0);
}

void	populate_cmd_args(t_minishell *mini)
{
	t_token	*token;
	t_cmd	*cmd;
	int		len_token;
	int		i;
	
	i = 0;
	token = mini->token;
	cmd = mini->cmd;
	len_token = token_list_size(token, mini);
	cmd->args = ft_calloc((token_list_size(token, mini) + 2), sizeof(char *));
	cmd->args[i] = ft_strdup(token->content);
	i++;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD && token->previous->type != is_redirect(mini))
		{
			cmd->args[i] = ft_strdup(token->content);
			i++;
		}
		token = token->next;
	}
	cmd->args[i] = NULL;
}

t_cmd	*cmd_new_node(t_minishell *mini)
{
	t_cmd *cmd;
	
	cmd = ft_calloc(1, sizeof(t_cmd));
	if(!cmd)
		return (NULL);
	cmd->name = ft_strdup(mini->token->content);
	cmd->args = NULL;
	cmd->type = mini->token->type;
	cmd->next = NULL;
	cmd->previous = NULL;
	return (cmd);
}


// GitHub Copilot: The `append_cmd_to_list` function is responsible for adding a new command to a list of commands in a `t_minishell` structure.

//The purpose of this function is to maintain a list of commands that the `t_minishell` structure needs to execute. Each command is represented by a `t_cmd` structure, and the commands are linked together in a doubly linked list. When a new command is created, it is added to the end of this list by the `append_cmd_to_list` function.

void append_cmd_to_list(t_minishell *mini)
{
	t_cmd	*cmd;
	
	if(mini->list_cmd == NULL)
	{
		mini->list_cmd = mini->cmd;
		return ;
	}
	cmd = mini->list_cmd;
	while (cmd->next)
		cmd = cmd->next;
	cmd->next = mini->cmd;
	cmd->next->previous = cmd;
}

void	add_cmd(t_minishell *mini, t_cmd **cmd, int *count)
{
	*count = 1;
	*cmd = cmd_new_node(mini);
	populate_cmd_args(mini);
	append_cmd_to_list(mini);
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
			add_cmd(mini, &cmd, &count);
		else
			token = token->next;
	}
}