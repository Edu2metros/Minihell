/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunsigned_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:39:48 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 17:01:51 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_unsint_fd(unsigned int nbr, int fd)
{
	int	size;

	size = 0;
	if (nbr < 10)
		size += putchar_fd(nbr + '0', fd);
	else
	{
		size += putnbr_fd(nbr / 10, fd);
		size += putchar_fd(nbr % 10 + '0', fd);
	}
	return (size);
}
