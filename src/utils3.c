/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:05:06 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 20:06:57 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isalpha_mini(char input)
{
	if (!input || input == '\0')
		return (0);
	if (input == '"' || input == '\'')
		return (1);
	else
		return (ft_isalpha(input));
}

int	handle_error_two(char *prompt)
{
	if (*prompt == '|' || prompt[ft_strlen(prompt) - 1] == '|')
	{
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected \
            token `|'\n");
		get_control()->return_status = 2;
		return (0);
	}
	return (1);
}

int	handle_quote_val(char *prompt, int *i)
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

int	handle_pipe_char(char *prompt, int *i)
{
	if (prompt[*i] == '|')
	{
		if (!ft_redirect(prompt, *i + 1))
		{
			ft_printf_fd(STDERR_FILENO, "minishell: syntax error near \
            unexpected token `|'\n");
			get_control()->return_status = 2;
			return (0);
		}
	}
	return (1);
}

int	handle_pipe(char *prompt)
{
	int	i;

	i = 0;
	if (!handle_error_two(prompt))
		return (0);
	while (prompt[i] != '\0')
	{
		if (!handle_quote_val(prompt, &i) || !handle_pipe_char(prompt, &i))
			return (0);
		i++;
	}
	return (1);
}
