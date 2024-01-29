/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:47:19 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/29 19:09:28 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	handle_error(int nbr)
{
	static char *message[2] = {
		"Please close the quotes.",
		"Syntax error.",
	};
	printf("%s\n", message[nbr]);
}

int	meta_char(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	ft_redirect(char *prompt, int i)
{
	while (prompt[i] != '\0' && (my_isspace(prompt[i])
			&& !meta_char(prompt[i])))
		i++;
	if (prompt[i] == '\0' || my_isspace(prompt[i]) || meta_char(prompt[i]))
		return (0);
	return (1);
}

bool	validator(char *prompt)
{
	int	i;

	if (check_quote(prompt) == 0 || prompt[0] == '|' || prompt[ft_strlen(prompt)
			- 1] == '|')
	{
		handle_error(1);
		return (false);
	}
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '>')
		{
			if (prompt[i + 1] == '>' || !ft_redirect(prompt, i + 1))
			{
				handle_error(1);
				return (false);
			}
		}
		i++;
	}
	return (true);
}
