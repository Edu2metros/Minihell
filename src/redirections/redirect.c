/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:12:19 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/27 21:16:30 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_files(char *file_name)
{
	if (access(file_name, F_OK) == 0)
		return (EXIST);
	if (access(file_name, R_OK) == 0)
		return (READABLE);
	if (access(file_name, W_OK) == 0)
		return (WRITEABLE);
	if (access(file_name, X_OK) == 0)
		return (EXECUTABLE);
	else
		return (0);
}

void	handle_out_files(t_redirect_out *redirect)
{
	char	*file;

	file = redirect->content;
	if (redirect->type == OUTPUT)
		redirect->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if(redirect->type == APPEND)
		redirect->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);	
}

void	handle_in_files(t_redirect_out *redirect)
{
	char	*file;

	if (redirect->type == INPUT)
	{
		file = redirect->content;
		redirect->fd = open(file, O_RDONLY); // only reads the file, instead wait for a command like cat < texto.txt
	}
	// checl if we will treat heredoc here, or if is that another way(?)
}

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

t_redirect_out	*add_redirect_out(t_redirect_out *redirect, char *content,
		int type)
{
	t_redirect_out	*new;

	if (!redirect)
		return (new_redirect_out(content, type));
	new = NULL;
	new = new_redirect_out(content, type);
	redirect->next = new;
	return (new);
}

t_redirect_out	*lstlast(t_redirect_out *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	redirect_out_list(t_token **token, t_redirect_out *redirect)
{
	t_redirect_out	*new_red;

	while (*token)
	{
		if ((*token)->type == OUTPUT)
		{
			if (check_files((*token)->next->content) == EXIST)
				if (check_files((*token)->next->content) != WRITEABLE)
					handle_error(0);
				else if (check_files((*token)->next->content) == EXECUTABLE)
					handle_error(0); // Diretório
		}
		new_red = add_redirect_out(redirect, (*token)->next->content,
			(*token)->type);
		if (new_red != NULL)
		{
			if (redirect_out_list == NULL)
				redirect_out_list = new_red;
			else
				lstlast(redirect_out_list) == new_red;
			handle_out_files(new_red);
		}
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

t_redirect_in	*add_redirect_in(t_redirect_in *redirect, char *content,
		int type)
{
	t_redirect_in	*new;

	if (!redirect)
		return (new_redirect_in(content, type));
	new = NULL;
	new = new_redirect_in(content, type);
	redirect->next = new;
	return (new);
}

void	redirect_in_list(t_token **token, t_redirect_out *redirect)
{
	t_redirect_out	*new_red;

	while (*token)
	{
		if ((*token)->type == INPUT)
		{
			if (!check_files((*token)->next->content) == EXIST)
					handle_error(0);
			else if (!check_files((*token)->next->content) == READABLE)
					handle_error(0); // Permission
		}
		new_red = add_redirect_in(redirect, (*token)->next->content,
			(*token)->type);
		if (new_red != NULL)
		{
			if (redirect_in_list == NULL)
				redirect_in_list = new_red;
			else
				lstlast(redirect_in_list) == new_red;
			handle_in_files(new_red);
		}
		*token = (*token)->next;
	}
}

// add_redirect_in(redirect, (*token)->content, (*token)->type);
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