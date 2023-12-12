/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:11:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/08/09 18:49:54 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int bytes, size_t memory)
{
	size_t			memorycpy;
	unsigned char	*ptr;

	memorycpy = 0;
	ptr = (unsigned char *)s;
	while (memorycpy < memory)
	{
		ptr[memorycpy] = (unsigned char)bytes;
		memorycpy++;
	}
	return (s);
}
