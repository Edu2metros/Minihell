/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthex_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:38:35 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/12 17:47:48 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_fd(unsigned int nbr, char x, int fd)
{
	int	size;
	int	digit;

	size = 0;
	if (nbr / 16 > 0)
		size += ft_puthex_fd(nbr / 16, x, fd);
	digit = nbr % 16;
	if (digit < 10)
		size += putchar_fd('0' + digit, fd);
	else
	{
		if (x == 'x')
			size += putchar_fd('a' + digit - 10, fd);
		else if (x == 'X')
			size += putchar_fd('A' + digit - 10, fd);
	}
	return (size);
}
