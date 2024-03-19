/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:33:51 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/18 20:28:29 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_in *new_redirect_in(char *content, int type)
{
	t_redirect_in *redirect;

	redirect = malloc(sizeof(t_redirect_in));
	if (!redirect)
		return (NULL);
	redirect->type = type;
	redirect->content = ft_strdup(content);
	redirect->fd_in = -1;
	redirect->next = NULL;
	return (redirect);
}

int check_in_files(char *str)
{
	if (!file_exist(str))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", str);
		return (0);
	}
	else if (!file_is_readable(str))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
		return (0);
	}
	return (1);
}

void set_heredoc(t_token **token, t_redirect_in **redirect, t_cmd *cmd)
{
	t_redirect_in *new_red_in;
	t_redirect_in *last;

	last = lstlast_in(*redirect);
	new_red_in = new_redirect_in("heredoc", (*token)->type);
	if (new_red_in != NULL)
	{
		if (*redirect == NULL)
			*redirect = new_red_in;
		else
			last->next = new_red_in;
		get_heredoc(cmd);
	}
	*token = (*token)->next;
}

void redirect_in_list(t_token **token, t_redirect_in **redirect)
{
	t_redirect_in *new_red_in;
	t_redirect_in *last;

	last = lstlast_in(*redirect);
	if (!check_in_files((*token)->next->content))
	{
		clear_list_in(redirect);
		return;
	}
	new_red_in = new_redirect_in((*token)->next->content, (*token)->type);
	if (new_red_in != NULL)
	{
		if (*redirect == NULL)
			*redirect = new_red_in;
		else
			last->next = new_red_in;
		handle_in_files(new_red_in);
	}
	*token = (*token)->next;
}

void clear_list_in(t_redirect_in **redirect)
{
	t_redirect_in *tmp;

	if (!redirect)
		return ;
	while (*redirect)
	{
		tmp = (*redirect)->next;
		if ((*redirect)->heredoc == 0)
		{
			close((*redirect)->fd_in);
			free((*redirect)->content);
			free(*redirect);
		}
		else if ((*redirect)->heredoc == 1)
		{
			close((*redirect)->fd_in);
			unlink((*redirect)->content);
			free((*redirect)->content);
			free(*redirect);
		}
		*redirect = tmp;
	}
}