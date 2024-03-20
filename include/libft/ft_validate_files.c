/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:47:15 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 20:47:31 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
