/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:39:34 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 16:55:51 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	putstr_fd(char *str, int fd)
{
	size_t	size;

	size = 0;
	if (str == NULL)
		str = "(null)";
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
		size++;
	}
	return (size);
}
