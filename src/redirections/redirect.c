/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:12:19 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/27 14:32:19 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_out	*new_redirect_out(char *content, int type)
{
	t_redirect_out	*redirect;

	redirect = malloc(sizeof(t_redirect_out));
	redirect->type = type;
	redirect->content = ft_strdup(content);
	redirect->fd = 0;
	redirect->next = NULL;
	return (redirect);
}

t_redirect_out	*add_redirect_out(t_redirect_out *redirect, char *content, int type)
{
	t_redirect_out	*new;

	if (!redirect)
		return (new_redirect_out(content, type));
	new = NULL;
	new = new_redirect_out(content, type);
	redirect->next = new;
	return (new);
}

void	redirect_out_list(t_token **token, t_redirect_out *redirect)
{
	while (*token)
	{
		if ((*token)->type == OUTPUT || (*token)->type == APPEND)
			add_redirect_out(redirect, (*token)->content, (*token)->type);
		*token = (*token)->next;
	}
}

t_redirect_in	*new_redirect_in(char *content, int type)
{
	t_redirect_in	*redirect;

	redirect = malloc(sizeof(t_redirect_in));
	redirect->type = type;
	redirect->content = ft_strdup(content);
	redirect->fd = 0;
	redirect->next = NULL;
	return (redirect);
}

t_redirect_in	*add_redirect_in(t_redirect_in *redirect, char *content, int type)
{
	t_redirect_in	*new;

	if (!redirect)
		return (new_redirect_in(content, type));
	new = NULL;
	new = new_redirect_in(content, type);
	redirect->next = new;
	return (new);
}

void	redirect_in_list(t_token **token, t_redirect_in *redirect)
{
	while (*token)
	{
		if ((*token)->type == OUTPUT || (*token)->type == APPEND)
			add_redirect_in(redirect, (*token)->content, (*token)->type);
		*token = (*token)->next;
	}
}

/* void	ft_redirect_out(t_minishell *mini)
{
	t_token	*token;
	char	*outfile;
	int		fd;

	token = mini->token;
	while (token)
	{
		if (token->type == OUTPUT && token->next->type == WORD)
		{
			outfile = token->next->content;
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				exit(EXIT_FAILURE);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		token = token->next;
	}
} */
