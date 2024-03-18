/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/18 11:32:08 by eddos-sa         ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*new_node(char *content, int type)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(content);
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->type = type;
	cmd->previous = NULL;
	cmd->on_fork = 0;
	cmd->count = 0;
	cmd->redirect_list_in = NULL;
	cmd->redirect_list_out = NULL;
	return (cmd);
}

void	add_last(t_cmd **cmd, t_cmd *aux)
{
	if (*cmd == NULL)
	{
		*cmd = aux;
		return ;
	}
	while ((*cmd)->next != NULL)
		*cmd = (*cmd)->next;
	(*cmd)->next = aux;
	aux->previous = *cmd;
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
	cmd->on_fork = 0;
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

t_cmd *lstlast_cmd(void)
{
	t_cmd	*aux;

	aux = get_control()->cmd;
	while (aux->next)
		aux = aux->next;
	return (aux);
}

void	create_cmd_list(t_minishell *mini)
{
	t_token	*token;
	int		count;

	token = mini->token;
	count = 0;
	while (token)
	{
		add_last(&mini->cmd, new_node(token->content, token->type));
		token = populate_cmd_args(token, lstlast_cmd(), mini);
		get_heredoc();
		if (get_control()->heredoc)
			return ;
		if (token != NULL)
			token = token->next;
	}
	// handle_redirects(mini);
	// remove_redirect(mini->cmd);
}
