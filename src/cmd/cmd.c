/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/01 17:18:45 by eddos-sa         ###   ########.fr       */
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

int	expand_variable(t_token *token, char *input, int i)
{
	int		start;
	char	*substr;

	start = i;
	while (!is_quote(input[i]) && !my_isspace(input[i]) && !meta_char(input[i])
		&& input[i] != '$')
		i++;
	substr = ft_substr(input, start, i - start);
	printf("%s\n", substr);
	if (getenv(substr) != NULL)
	{
		
	}
	printf("%s\n", token->content);
	free(substr);
	return (i);
}

void	handle_quote(t_token *token)
{
	char	*substr;
	int		i;
	int		start;
	char	type;

	i = 0;
	type = token->content[0];
	if (token->type == QUOTE)
	{
		substr = ft_strdup(token->content);
		free(token->content);
		while (substr[i] == type)
			i++;
		start = i;
		while (substr[i])
		{
			if (substr[i] == type)
				i++;
			else if (substr[i] == '$' && type == '"')
			{
				i = expand_variable(token, substr, i + 1);
			}
			else
			{
				// token->content = strcat(token->content, substr);
				i++;
			}
		}
	}
}

void	populate_cmd_args(t_token **token, t_cmd *cmd)
{
	cmd->args = ft_calloc(lstsize_pipe(*token) + 1, sizeof(char *));
	if (!cmd->args)
		return ;
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == WORD || (*token)->type == DOLLAR
			|| (*token)->type == QUOTE)
		{
			handle_quote(*token);
			cmd->args[cmd->count] = ft_strdup((*token)->content);
			cmd->count++;
		}
		*token = (*token)->next;
	}
	cmd->args[cmd->count] = NULL;
	cmd->count = 0;
}
