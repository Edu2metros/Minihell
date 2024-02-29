/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:10:27 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/29 15:10:33 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_quote(char *input)
{
	int		i;
	char	type;

	i = 0;
	type = 0;
	while (*input != '\0')
	{
		if (*input == '\'' || *input == '"')
			break ;
		input++;
	}
	if (!*input)
		return (2);
	type = *input;
	while (*input != '\0')
	{
		if (*input == type)
			i++;
		input++;
	}
	return (i % 2 == 0);
}
