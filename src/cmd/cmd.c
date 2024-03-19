/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 16:19:51 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*add_new_node(t_cmd *cmd, char *content, int type, int space)
{
	t_cmd	*new;

	if (!cmd)
		return (cmd_new_node(content, type, space));
	new = NULL;
	new = cmd_new_node(content, type, space);
	new->previous = cmd;
	cmd->next = new;
	return (new);
}

t_cmd	*cmd_new_node(char *content, int type, int space)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (!ft_isredirect(content))
		cmd->name = ft_strdup(content);
	else
		cmd->name = NULL;
	cmd->space = space;
	cmd->on_fork = 0;
	cmd->return_status = 0;
	cmd->type = type;
	cmd->args = NULL;
	cmd->count = 0;
	cmd->next = NULL;
	cmd->previous = NULL;
	cmd->redirect_list_in = NULL;
	cmd->redirect_list_out = NULL;
	return (cmd);
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

void	create_cmd_list(t_minishell *mini)
{
	t_token	*token;
	int		count;

	token = mini->token;
	count = 0;
	while (token)
	{
		mini->cmd = add_new_node(mini->cmd, token->content, token->type, \
			token->space);
		token = populate_cmd_args(token, mini->cmd, mini);
		if (token != NULL)
			token = token->next;
	}
	handle_redirects(mini);
	remove_redirect(mini->cmd);
}
