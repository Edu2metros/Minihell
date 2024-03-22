/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:24:19 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/22 20:24:24 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int    ft_strcmp_len(char *s1, char *s2)
{
    if (ft_strlen(s1) == ft_strlen(s2))
        return (ft_strncmp(s1, s2, __UINT64_MAX__) == 0);
    return (0);
}
