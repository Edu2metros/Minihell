/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_equals_chr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:23:46 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/22 20:23:54 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int    count_equals_chr(char *str, char c)
{
    int    i;
    int    equals;

    i = 0;
    equals = 0;
    if (str == NULL || *str == '\0')
        return (equals);
    while (str[i])
    {
        if (str[i] == c)
            equals++;
        i++;
    }
    return (equals);
}
