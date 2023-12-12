/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:15:09 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/08/09 18:50:04 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int					i;
	const unsigned char	*str;
	unsigned char		chr;

	str = (const unsigned char *)s;
	chr = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (chr == str[i])
			return ((char *)&str[i]);
		i++;
	}
	if (chr == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
