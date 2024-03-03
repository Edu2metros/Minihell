/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/03 16:52:45 by eddos-sa         ###   ########.fr       */
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

	cmd = malloc(sizeof(t_cmd));
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
		if (token->type == PIPE)
			return (i);
		i++;
		token = token->next;
	}
	return (i);
}

int	expand_variable(t_token *token, int i)
{
	char	*substr;
	int		start;

	start = i;
	while (ft_isalnum(token->content[i]) || token->content[i] == '_')
		i++;
	substr = ft_substr(token->content, start, i - start);
	if (getenv(substr) != NULL)
		token->aux = ft_strjoin(token->aux, getenv(substr));
	return (i);
}

void	handle_quote(t_token *token)
{
	int		i;
	char	type;
	int		start;

	i = 0;
	type = token->content[0];
	if (token->type == QUOTE)
	{
		token->aux = ft_strdup("");
		while (token->content[i] == type)
			i++;
		start = i;
		while (token->content[i])
		{
			if (token->content[i] == type)
				i++;
			else if (token->content[i] == '$' && type == '"')
				i = expand_variable(token, i + 1);
			else
			{
				token->aux = ft_strjoin_char(token->aux, token->content[i]);
				i++;
			}
		}
		free(token->content);
		token->content = ft_strdup(token->aux);
		free(token->aux);
	}
}

void	next_quote(t_token *token)
{
	t_token	*current;
	t_token	*next;

	current = token;
	next = current->next;
	if (current->type == QUOTE)
	{
		handle_quote(current);
		if(current->space)
			current->content = ft_strjoin(current->content, " ");
		while (next != NULL && next->type == QUOTE)
		{
			handle_quote(next);
			current->content = ft_strjoin(current->content, next->content);
			if(next->space)
				current->content = ft_strjoin(current->content, " ");
			current->next = next->next;
			free(next->content);
			free(next);
			next = current->next;
		}
	}
}

void	populate_cmd_args(t_token *token, t_cmd *cmd)
{
	cmd->args = ft_calloc(lstsize_pipe(token) + 1, sizeof(char *));
	if (!cmd->args)
		return ;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD || token->type == DOLLAR
			|| token->type == QUOTE)
		{
			next_quote(token);
			cmd->args[cmd->count] = ft_strdup(token->content);
			cmd->count++;
		}
		token = token->next;
	}
	cmd->args[cmd->count] = NULL;
	cmd->count = 0;
}
