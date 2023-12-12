/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:01:05 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/08/10 13:00:24 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digits(int n);

char	*ft_itoa(int n)
{
	long int	num;
	size_t		digits;
	char		*result;

	num = n;
	digits = get_digits(num);
	if (n < 0)
	{
		num = -num;
		digits++;
	}
	result = (char *)malloc(sizeof(char) * (digits + 1));
	if (!result)
		return (NULL);
	*(result + digits) = 0;
	while (digits--)
	{
		*(result + digits) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*result = '-';
	return (result);
}

static size_t	get_digits(int n)
{
	int	size;

	size = 1;
	while (n / 10)
	{
		size++;
		n /= 10;
	}
	return (size);
}
