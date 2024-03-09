/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/08 21:26:57 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redirect(t_token *token)
{
	int	type;

	type = token->type;
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
	char	*tmp;
	int		start;

	start = i;
	while (ft_isalnum(token->content[i]) || token->content[i] == '_')
		i++;
	substr = ft_substr(token->content, start, i - start);
	tmp = hash_search(get_control()->table, substr);
	if (tmp != NULL)
		token->aux = ft_strjoin(token->aux, tmp);
	free(tmp);
	free(substr);
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
		if (current->space)
			current->content = ft_strjoin(current->content, " ");
		while (next != NULL && next->type == QUOTE)
		{
			handle_quote(next);
			current->content = ft_strjoin(current->content, next->content);
			if (next->space)
				current->content = ft_strjoin(current->content, " ");
			current->next = next->next;
			free(next->content);
			free(next);
			next = current->next;
		}
	}
}

t_token	*populate_cmd_args(t_token *token, t_cmd *cmd, t_minishell *mini)
{
	cmd->args = ft_calloc(lstsize_pipe(token) + 1, sizeof(char *));
	if (!cmd->args)
	{
		printf("Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	while (token && token->type != PIPE)
	{
		if (is_redirect(token))
		{
			handle_redirects(cmd, mini);
		}
		next_quote(token);
		cmd->args[cmd->count] = ft_strdup(token->content);
		cmd->count++;
		token = token->next;
	}
	cmd->args[cmd->count] = NULL;
	cmd->count = 0;
	return (token);
}


void	create_cmd_list(t_minishell *mini)
{
	t_token	*token;
	int		count;

	token = mini->token;
	count = 0;
	while (token)
	{
		mini->cmd = add_new_node(mini->cmd, (mini->token)->content,
			(mini->token)->type);
		token = populate_cmd_args(token, mini->cmd, mini);
		if (token && token->type == PIPE)
		{
			mini->cmd = add_new_node(mini->cmd,	token->content, token->type);
			mini->cmd->args = ft_calloc(1, sizeof(char *));
			mini->cmd->args[0] = ft_strdup("|");
			mini->cmd->args[1] = NULL; 
		}
		if (token != NULL)
			token = token->next;
	}
	print_cmd_args(mini->cmd);
}



// free_tokens(&token);
// print_cmd_args(mini->cmd);

/* 		if (token == PIPE)
		{
			last_cmd = get_last_cmd();
			last_cmd->output_to_pipe = true;
		}

			se o token atual é um comando,
				e o ultimo comando da lista de commandos
			vai escrever em um pipe,
				introduzimos um novo comando na lista de comandos
			e definimos que esse novo comando vai ler de um pipe.

		else if (token == COMMAND && get_last_cmd()->output_to_pipe == true)
		{
			append_command(type, ...);
			get_last_cmd()->input_from_pipe = true;
		} */