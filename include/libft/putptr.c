/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:35:08 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/11/18 14:12:07 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	puthex(unsigned long int nbr, char x);

int	ft_putptr(void *ptr)
{
	int	size;

	size = 0;
	if (!ptr)
	{
		size += ft_putstr("(nil)");
		return (size);
	}
	size += ft_putstr("0x");
	size += puthex((unsigned long int)ptr, 'x');
	return (size);
}

static int	puthex(unsigned long int nbr, char x)
{
	int	size;
	int	digit;

	size = 0;
	if (nbr / 16 > 0)
		size += puthex(nbr / 16, x);
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
