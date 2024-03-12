/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunsigned_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:39:48 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/12 17:50:50 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_unsint_fd(unsigned int nbr, int fd)
{
    int size = 0;

    if (nbr < 10)
        size += putchar_fd(nbr + '0', fd);
    else
    {
        size += putnbr_fd(nbr / 10, fd);
        size += putchar_fd(nbr % 10 + '0', fd);
    }
    return size;
}
