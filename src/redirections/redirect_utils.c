/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:29:10 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/27 20:29:50 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_out	*lstlast(t_redirect_out *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

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