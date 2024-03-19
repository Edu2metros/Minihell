/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_hand_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:29:10 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 13:13:22 by eddos-sa         ###   ########.fr       */
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
		if (redirect->fd_out == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", file);
			get_control()->return_status = 1;
			return ;
		}
	}
	else if (redirect->type == APPEND)
	{
		redirect->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redirect->fd_out == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", file);
			get_control()->return_status = 1;
			return ;
		}
	}
}

void	handle_in_files(t_redirect_in *redirect)
{
	char	*file;

	if (redirect->type == HEREDOC)
	{
		redirect->heredoc = 1;
		redirect->fd_in = open("heredoc", O_RDONLY);
	}
	if (redirect->type == INPUT)
	{
		file = redirect->content;
		redirect->heredoc = 0;
		redirect->fd_in = open(file, O_RDONLY);
		if(redirect->fd_in == -1)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", file);
			get_control()->return_status = 1;
			return ;
		}
	}
}
