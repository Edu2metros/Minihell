/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:35:41 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 13:57:15 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_out *new_redirect_out(char *content, int type)
{
	t_redirect_out *redirect;

	redirect = malloc(sizeof(t_redirect_out));
	if (!redirect)
		return (NULL);
	redirect->type = type;
	redirect->content = ft_strdup(content);
	redirect->fd_out = -1;
	redirect->next = NULL;
	return (redirect);
}

int check_out_files(char *str, t_cmd *cmd)
{
    if (file_exist(str))
    {
    	if (!file_is_writable(str))
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", str);
			cmd->return_status = 1;
			return 0;
		}
	}
    if (file_is_executable(str))
    {
        ft_printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", str);
		cmd->return_status = 1;
        return 0;
    }
    return (1);
}

void redirect_out_list(t_token **token, t_redirect_out **redirect, t_cmd *cmd)
{
	t_redirect_out *new_red;
	t_redirect_out *last;

	last = lstlast_out(*redirect);
	if (!check_out_files((*token)->next->content, cmd))
	{
		clear_list_out(redirect);
		return;
	}
	new_red = new_redirect_out((*token)->next->content, (*token)->type);
	if (new_red != NULL)
	{
		if (*redirect == NULL)
			*redirect = new_red;
		else
			last->next = new_red;
		handle_out_files(new_red);
	}
	*token = (*token)->next;
}

void clear_list_out(t_redirect_out **redirect)
{
	t_redirect_out *tmp;

	if (!redirect)
		return;
	while (*redirect)
	{
		tmp = (*redirect)->next;
		close((*redirect)->fd_out);
		free((*redirect)->content);
		free(*redirect);
		*redirect = tmp;
	}
}