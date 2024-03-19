/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:16:51 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 17:05:49 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

long double	ft_atof(char *str)
{
	unsigned int	i;
	long double		sign;
	long double		result;
	long double		divisor;

	divisor = 0.1;
	i = 0;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = ((str[i] == '+' || ft_isdigit(str[i])) - (str[i] == '-'));
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]) && str[i] != '.')
		result = result * 10 + (str[i++] - '0');
	if (str[i] == '.')
	{
		while (str[++i] != '\0' && ft_isdigit(str[i]))
		{
			result += (str[i] - '0') * divisor;
			divisor /= 10;
		}
	}
	return (result * sign);
}

int	is_excession(char c)
{
	return (c == '.' || c == '/' || c == '=' || c == '$' || c == '\''
		|| c == '"');
	return (0);
}
