/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_hand_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:29:10 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/06 20:10:55 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	file_exist(char *file_name)
{
	if (access(file_name, F_OK) == -1)
		return (0);
	return (1);
}
int	file_is_readable(char *file_name)
{
	if (access(file_name, R_OK) == -1)
		return (0);
	return (1);
}

int	file_is_writable(char *file_name)
{
	if (access(file_name, W_OK) == -1)
		return (0);
	return (1);
}

int	file_is_executable(char *file_name)
{
	if (access(file_name, X_OK) == -1)
		return (0);
	return (1);
}

void	handle_out_files(t_redirect_out *redirect)
{
	char	*file;
	
	file = redirect->content;
	if (redirect->type == OUTPUT)
	{
		redirect->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("fd_out: %d\n", redirect->fd_out);
		if (redirect->fd_out == -1)
			return ;
	}
	else if (redirect->type == APPEND)
	{
		redirect->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		printf("fd_out: %d\n", redirect->fd_out);
		if (redirect->fd_out == -1)
			return ;
	}
}

void	handle_in_files(t_redirect_in *redirect)
{
	char	*file;

	if (redirect->type == INPUT)
	{
		file = redirect->content;
		redirect->fd_in = open(file, O_RDONLY);
		printf("fd_in: %d\n", redirect->fd_in);
	}
}
