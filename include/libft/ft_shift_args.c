/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shift_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:23:00 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/22 20:23:11 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    shift_args(char **args, int start)
{
    int    j;

    j = start;
    while (args[j])
    {
        args[j] = args[j + 1];
        j++;
    }
    free(args[j]);
}
