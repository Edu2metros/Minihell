/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:47:19 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/30 12:05:31 by eddos-sa         ###   ########.fr       */
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

bool	validator(char *prompt)
{
	int	i;

	i = 0;
	if (check_quote(prompt) == 0)
	{
		handle_error(0);
		return (0);
	}
	if (prompt[0] == '|' || prompt[ft_strlen(prompt) - 1] == '|')
	{
		handle_error(1);
		return (0);
	}
	while (prompt[i])
	{
		if (prompt[i] == '>')
		{
			if (prompt[i + 1] == '>')
			{
				if (!ft_redirect(prompt, i + 2))
				{
					handle_error(1);
					return (0);
				}
			}
			else
			{
				if (!ft_redirect(prompt, i + 1))
				{
					handle_error(1);
					return (0);
				}
			}
		}
		i++;
	}
	return (1);
}
