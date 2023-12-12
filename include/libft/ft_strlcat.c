/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:18:11 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/08/09 19:53:31 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	final_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	dest_len = ft_strlen(dst);
	final_len = dest_len + src_len;
	if (size > dest_len)
	{
		while ((*src != '\0') && (dest_len < size - 1))
			dst[dest_len++] = *src++;
		dst[dest_len] = '\0';
		return (final_len);
	}
	return (src_len + size);
}
