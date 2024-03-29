/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:47:19 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 19:05:57 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_quote_red(char *prompt, int *i)
{
	int	quote;

	if (is_quote(prompt[*i]))
	{
		quote = prompt[*i];
		(*i)++;
		while (prompt[*i] != quote)
			(*i)++;
	}
	return (1);
}

int	handle_char_red(char *prompt, char c, int *i)
{
	int	offset;

	offset = 1;
	if (prompt[*i] == c)
	{
		if (prompt[*i + 1] == c)
			offset++;
		if (!ft_redirect(prompt, *i + offset))
		{
			ft_printf_fd(STDERR_FILENO, "minishell: syntax error near \
unexpected token `%c'\n", c);
			get_control()->return_status = 2;
			return (0);
		}
	}
	return (1);
}

int	handle_red(char *prompt, char c)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (!handle_quote_red(prompt, &i) || !handle_char_red(prompt, c, &i))
			return (0);
		i++;
	}
	return (1);
}
