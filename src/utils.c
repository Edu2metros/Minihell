/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:47:19 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/15 17:50:50 by eddos-sa         ###   ########.fr       */
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

int	ft_redirect(char *prompt, int i)
{
	while (prompt[i] != '\0' && (my_isspace(prompt[i])
			&& !meta_char(prompt[i])))
		i++;
	if (prompt[i] == '\0' || my_isspace(prompt[i])
		|| !ft_isalpha_mini(prompt[i]))
		return (0);
	return (1);
}

int	handle_pipe(char *prompt)
{
	int	i;

	if (*prompt == '|' || prompt[ft_strlen(prompt) - 1] == '|')
	{
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	i = 0;
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '|')
		{
			if (!ft_redirect(prompt, i + 1))
			{
				ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token `|'\n");
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

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == c)
		{
			offset = 1;
			if (prompt[i + 1] == c)
				offset++;
			if (!ft_redirect(prompt, i + offset))
			{
				ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token `%c'\n", c);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	validator(char *prompt)
{
	if (prompt == NULL || *prompt == '\0')
		return (0);
	if (!handle_red(prompt, '<'))
		return (0);
	if (!handle_red(prompt, '>'))
		return (0);
	if (!handle_pipe(prompt))
		return (0);
	return (1);
}

void	ft_putstring_fd(int fd)
{
	int	c;

	while (read(fd, &c, 1) != -1)
		write(2, &c, 1);
}
