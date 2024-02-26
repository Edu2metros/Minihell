/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/26 17:25:38 by eddos-sa         ###   ########.fr       */
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

t_cmd	*add_new_node(t_cmd *cmd, char *content, int type)
{
	if(!cmd)
		return(cmd_new_node(content, type));
	t_cmd *new = NULL;
	new = cmd_new_node(content, type);
	new->previous = cmd;
	cmd->next = new;
	return(new);
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
	cmd->next = NULL;
	cmd->previous = NULL;
	return (cmd);
}

int	token_list_size(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		// if(token && token->previous->type != is_redirect(get_control()->))
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

void populate_cmd_args(t_minishell *mini, t_token **token, t_cmd *cmd)
{
    cmd->args = ft_calloc(500, sizeof(char *));
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
    cmd->args[cmd->count] = NULL;
	cmd->count = 0;
}


void	add_cmd(t_minishell *mini, t_token **token, t_cmd **cmd, int *count)
{
	*count = 1;
	*cmd = add_new_node(*cmd, (mini->token)->content, (mini->token)->type);
	populate_cmd_args(mini, token, *cmd);
/* 	printf("\n=========================  ARGS  =========================\n\n");
	print_cmd_args(*cmd); */
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
}

t_cmd	*lst_first(t_cmd *cmd)
{
	t_cmd	*result;

	result = cmd;
	while (result != NULL && result->previous != NULL)
		result = result->previous;
	return (result);
}
