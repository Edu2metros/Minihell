/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:34:58 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 16:52:20 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	format_fd(const char *str, va_list ap, int fd)
{
	size_t	size;

	size = 0;
	if (*str == 'c')
		size += putchar_fd(va_arg(ap, int), fd);
	else if (*str == 's')
		size += putstr_fd(va_arg(ap, char *), fd);
	else if (*str == 'p')
		size += ft_putptr_fd(va_arg(ap, void *), fd);
	else if (*str == 'd' || *str == 'i')
		size += putnbr_fd(va_arg(ap, int), fd);
	else if (*str == 'u')
		size += ft_unsint_fd(va_arg(ap, int), fd);
	else if (*str == 'x' || *str == 'X')
		size += ft_puthex_fd(va_arg(ap, int), *str, fd);
	else if (*str == '%')
		size += putchar_fd('%', fd);
	return (size);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	size_t	sizetotal;
	size_t	size;
	va_list	ap;

	sizetotal = 0;
	size = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			size = format_fd(++str, ap, fd);
			sizetotal += size;
		}
		else
		{
			size = putchar_fd(*str, fd);
			sizetotal += size;
		}
		str++;
	}
	va_end(ap);
	return (sizetotal);
}
