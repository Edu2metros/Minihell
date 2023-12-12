/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:46:22 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/11/18 14:12:16 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr(char *str)
{
	size_t	size;

	size = 0;
	if (str == NULL)
		str = "(null)";
	while (*str)
	{
		ft_putchar(*str);
		str++;
		size++;
	}
	return (size);
}
