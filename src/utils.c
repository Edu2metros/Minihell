/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:47:19 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 16:28:59 by jaqribei         ###   ########.fr       */
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

int	handle_pipe(char *prompt)
{
	int	i;
	int	quote;

	if (*prompt == '|' || prompt[ft_strlen(prompt) - 1] == '|')
	{
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected \
			token `|'\n");
		get_control()->return_status = 2;
		return (0);
	}
	i = 0;
	while (prompt[i] != '\0')
	{
		if (is_quote(prompt[i]))
		{
			quote = prompt[i];
			i++;
			while (prompt[i] != quote)
				i++;
		}
		if (prompt[i] == '|')
		{
			if (!ft_redirect(prompt, i + 1))
			{
				ft_printf_fd(STDERR_FILENO, "minishell: syntax error near \
				unexpected token `|'\n");
				get_control()->return_status = 2;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	handle_red(char *prompt, char c)
{
	int	i;
	int	offset;
	int	quote;

	i = 0;
	while (prompt[i])
	{
		if (is_quote(prompt[i]))
		{
			quote = prompt[i];
			i++;
			while (prompt[i] != quote)
				i++;
		}
		if (prompt[i] == c)
		{
			offset = 1;
			if (prompt[i + 1] == c)
				offset++;
			if (!ft_redirect(prompt, i + offset))
			{
				ft_printf_fd(STDERR_FILENO, "minishell: syntax error near \
				unexpected token `%c'\n", c);
				get_control()->return_status = 2;
				return (0);
			}
		}
		i++;
	}
	return (1);
}
