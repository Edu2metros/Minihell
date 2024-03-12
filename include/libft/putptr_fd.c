/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:39:15 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/12 17:49:18 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int puthex_fd(unsigned long int nbr, char x, int fd)
{
    int size = 0;
    int digit;

    if (nbr / 16 > 0)
        size += puthex_fd(nbr / 16, x, fd);
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
    return size;
}

size_t ft_putptr_fd(void *ptr, int fd)
{
    int size = 0;

    if (!ptr)
    {
        size += putstr_fd("(nil)", fd);
        return size;
    }
    size += putstr_fd("0x", fd);
    size += puthex_fd((unsigned long int)ptr, 'x', fd);
    return size;
}
