/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:08:33 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/29 15:12:30 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_error(int nbr)
{
	static char	*message[2] = {
		"Please close the quotes.",
		"Syntax error.",
	};

	printf("%s\n", message[nbr]);
}
