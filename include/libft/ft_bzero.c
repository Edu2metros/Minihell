/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:16:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/20 10:35:44 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;
	size_t			mem;

	c = (unsigned char *)s;
	mem = 0;
	while (mem < n)
	{
		c[mem] = 0;
		mem++;
	}
}

int	alpha_num(char c)
{
	if (c >= 33 && c <= 47)
		return (1);
	return (0);
}
