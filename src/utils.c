/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:47:19 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/07 20:13:04 by jaqribei         ###   ########.fr       */
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

/*
Validations to do:
Two or more redirections, pipes, or special chars, for example:
-> ||
-> >>>
-> <>
-> ><>
-> >>>
and etc...
*/

int	handle_pipe(char *prompt)
{
	int	i;

	if (*prompt == '|' || prompt[ft_strlen(prompt) - 1] == '|')
	{
		handle_error(1);
		return (0);
	}
	i = 0;
	while (prompt[i] != '\0')
	{
		if (prompt[i] == '|')
		{
			if (!ft_redirect(prompt, i + 1))
			{
				handle_error(1);
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
				handle_error(1);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

bool	validator(char *prompt)
{
	if (prompt == NULL || *prompt == '\0')
		return (false);
	if (!handle_red(prompt, '<'))
		return (false);
	if (!handle_red(prompt, '>'))
		return (false);
	if (!handle_pipe(prompt))
		return (false);
	return (true);
}

// void	handle_error(int nbr)
// {
// 	static char	*message[2] = {
// 		"Please close the quotes.",
// 		"Syntax error.",
// 	};

// 	printf("%s\n", message[nbr]);
// }
