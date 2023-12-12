/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:00:37 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/12/07 18:23:34 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unsint(unsigned int nbr)
{
	int	size;

	size = 0;
	if (nbr < 10)
		size += ft_putchar(nbr + '0');
	else
	{
		size += ft_putnbr(nbr / 10);
		size += ft_putchar(nbr % 10 + '0');
	}
	return (size);
}
