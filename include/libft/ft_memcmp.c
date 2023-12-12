/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:10:21 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/12/07 18:25:50 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	size_t			i;
	unsigned char	byte1;
	unsigned char	byte2;

	i = 0;
	while (i < n)
	{
		byte1 = *((const unsigned char *)ptr1 + i);
		byte2 = *((const unsigned char *)ptr2 + i);
		if (byte1 != byte2)
			return (byte1 - byte2);
		i++;
	}
	return (0);
}
