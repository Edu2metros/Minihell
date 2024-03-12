/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putint_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:38:56 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/12 17:48:48 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	putnbr_fd(int nbr, int fd)
{
	int	size;

	size = 0;
	if (nbr == -2147483648)
	{
		size += write(fd, "-", 1);
		size += putnbr_fd(2, fd);
		size += putnbr_fd(147483648, fd);
	}
	else if (nbr >= 0 && nbr < 10)
		size += putchar_fd(nbr + '0', fd);
	else if (nbr > 9)
	{
		size += putnbr_fd(nbr / 10, fd);
		size += putchar_fd(nbr % 10 + '0', fd);
	}
	else
	{
		size += putchar_fd('-', fd);
		size += putnbr_fd(nbr * -1, fd);
	}
	return (size);
}
