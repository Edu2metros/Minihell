/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/16 18:59:32 by eddos-sa         ###   ########.fr       */
=======
/*   Updated: 2024/03/16 18:19:59 by jaqribei         ###   ########.fr       */
>>>>>>> 09936e87005442f04853962545fd3648df6b2282
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (!ft_isredirect(content))
		cmd->name = ft_strdup(content);
	else
		cmd->name = NULL;
	cmd->type = type;
	cmd->args = NULL;
	cmd->count = 0;
	cmd->next = NULL;
	cmd->previous = NULL;
	cmd->redirect_list_in = NULL;
	cmd->redirect_list_out = NULL;
	return (cmd);
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
		ft_printf_fd(STDERR_FILENO, "minishell: Allocation error\n");
		exit(EXIT_FAILURE);
	}
	while (token && token->type != PIPE)
	{
		next_quote(token);
		cmd->args[cmd->count] = ft_strdup(token->content);
		cmd->count++;
		token = token->next;
	}
	cmd->args[cmd->count] = NULL;
	cmd->count = 0;
	return (token);
}

void	shift_args(char **args, int start)
{
	int	j;

	j = start;
	while (args[j])
	{
		args[j] = args[j + 1];
		j++;
	}
	free(args[j]);
}

void	remove_redirect(t_cmd *cmd)
{
	t_cmd	*aux;
	int		i;

	aux = lst_first(cmd);
	while (aux)
	{
		i = 0;
		while (aux->args[i])
		{
			if (ft_strcmp(aux->args[i], ">") == 0 || ft_strcmp(aux->args[i],
					">>") == 0 || ft_strcmp(aux->args[i], "<") == 0)
			{
				free(aux->args[i]);
				shift_args(aux->args, i);
				if (aux->args[i])
				{
					free(aux->args[i]);
					shift_args(aux->args, i);
				}
				if (aux->args[i] && !ft_isredirect(aux->args[i]))
					aux->name = ft_strdup(aux->args[i]);
			}
			else if (ft_strcmp(aux->args[i], "<<") == 0)
			{
				free(aux->args[i]);
				shift_args(aux->args, i);
				if (aux->args[i])
				{
					free(aux->args[i]);
					unlink("heredoc");
					shift_args(aux->args, i);
				}
				if (aux->args[i] && !ft_isredirect(aux->args[i]))
					aux->name = ft_strdup(aux->args[i]);
			}
			else
				i++;
		}
		aux = aux->next;
	}
}

void	create_cmd_list(t_minishell *mini)
{
	t_token *token;
	int count;

	token = mini->token;
	count = 0;
	while (token)
	{
		mini->cmd = add_new_node(mini->cmd, token->content, token->type);
		token = populate_cmd_args(token, mini->cmd, mini);
		get_heredoc();
		if (get_control()->heredoc)
			return ;
		handle_redirects(mini->cmd, mini);
		remove_redirect(mini->cmd);
		if (token != NULL)
			token = token->next;
	}
}
