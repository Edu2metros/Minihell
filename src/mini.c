/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:05:18 by jaqribei          #+#    #+#             */
/*   Updated: 2024/01/19 14:55:28 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int	is_operator(char *input, t_minishell *mini)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
			return (DOUBLE_GREAT);
		else if (input[i] == '<' && input[i + 1] == '<')
			return (DOUBLE_LESS);
		else if (input[i] == '>' && input[i + 1] != '>')
			return (GREAT);
		else if (input[i] == '<' && input[i + 1] != '<')
			return (LESS);
		else if (input[i] == '|')
			return (PIPE);
		i++;
	}
	return (1);
}

/* define if is random word, to use on tokenization later
its possibel to return the word, but let this part out for now */

int	is_word(const char *input, t_minishell *mini)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0')
	{
		if (ft_isalpha(input[i]) == 1)
		{
			while (input[i] != ' ' && input[i] != '\0')
				i++;
			return (WORD);
		}
	}
	return (1);
}

/* define if is argument, to use on tokenization later
its possibel to return the arg, but let this part out for now */

int	is_arg(const char *input, t_minishell *mini)
{
	int	i;


	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0')
	{
		if (input[i] == '-' && ft_isalpha(input[i + 1]) == 1 )
		{
			while (input[i] != ' ' && input[i] != '\0')
				i++;
			return (ARG);
		}
	}
	return (1);
}

/* thinking about do the same stuff to the commands bultins 
will write the functions, then we decide if is usefull to merge
with the previous idea to make our token list*/