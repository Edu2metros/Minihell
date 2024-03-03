/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:15:58 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/03 17:59:08 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*strdup;
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\0')
		i++;
	strdup = (char *)malloc((i + 1) * sizeof(char));
	if (strdup == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		strdup[j] = str[j];
		j++;
	}
	strdup[j] = '\0';
	return (strdup);
}
