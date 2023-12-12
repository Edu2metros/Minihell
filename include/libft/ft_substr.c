/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:21:20 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/08/11 11:34:25 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	src_len;
	size_t	str_len;

	src_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start < src_len)
		str_len = src_len - start;
	if (start >= src_len)
		return (ft_strdup(""));
	if (str_len > len)
		str_len = len;
	str = (char *)malloc(str_len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, (s + start), (str_len + 1));
	return (str);
}
