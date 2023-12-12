/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:45:17 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/11/18 14:11:55 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned int nbr, char x)
{
	int	size;
	int	digit;

	size = 0;
	if (nbr / 16 > 0)
		size += ft_puthex(nbr / 16, x);
	digit = nbr % 16;
	if (digit < 10)
		size += ft_putchar('0' + digit);
	else
	{
		if (x == 'x')
			size += ft_putchar('a' + digit - 10);
		else if (x == 'X')
			size += ft_putchar('A' + digit - 10);
	}
	return (size);
}
