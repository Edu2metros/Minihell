/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:29:10 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/28 13:32:42 by jaqribei         ###   ########.fr       */
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
	// check if we will treat heredoc here, or if is that another way(?)
}