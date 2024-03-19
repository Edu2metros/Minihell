/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:05:21 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 16:07:43 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	only_space(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] != '\0')
	{
		if (!my_isspace(prompt[i]))
			return (1);
		i++;
	}
	return (0);
}

int	validator(char *prompt)
{
	if (prompt == NULL || *prompt == '\0')
		return (0);
	if (!only_space(prompt))
		return (0);
	if (!check_quotes(prompt))
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

int	check_quotes(char *prompt)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '"' || prompt[i] == '\'')
		{
			if (quote == 0)
				quote = prompt[i];
			else if (quote == prompt[i])
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected \
		token `newline'\n");
		get_control()->return_status = 2;
		return (0);
	}
	return (1);
}

int	ft_redirect(char *prompt, int i)
{
	while (prompt[i] != '\0' && (my_isspace(prompt[i])
			&& !meta_char(prompt[i])))
		i++;
	if (prompt[i] == '\0' || my_isspace(prompt[i])
		|| meta_char(prompt[i]))
		return (0);
	return (1);
}
