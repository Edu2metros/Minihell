/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 03:16:37 by jaqribei          #+#    #+#             */
/*   Updated: 2024/01/24 15:40:02 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_quote(char c)
{
	if (c == '\'' )
		return (QUOTE);
	else if (c == '"')
		return (DOUBLE_QUOTE);
	else
		return (0);
}

int	is_operator(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0')
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
	return (0);
}

int	is_word(const char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0' && ft_isalnum(input[i]))
	{
		while (input[i] != ' ' && input[i] != '\0')
			i++;
		return (WORD);
	}
	return (0);
}

int	is_arg(const char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0')
	{
		if (input[i] == '-' && ft_isalpha(input[i + 1]) == 1)
		{
			while (input[i] != ' ' && input[i] != '\0')
				i++;
			return (ARG);
		}
		i++;
	}
	return (0);
}

int	is_builtin(char *input)
{
	if (ft_strncmp(input, "echo", 4) == 0)
		return (ECHO);
	else if (ft_strncmp(input, "cd", 2) == 0)
		return (CD);
	else if (ft_strncmp(input, "pwd", 3) == 0)
		return (PWD);
	else if (ft_strncmp(input, "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(input, "unset", 5) == 0)
		return (UNSET);
	else if (ft_strncmp(input, "env", 3) == 0)
		return (ENV);
	else if (ft_strncmp(input, "exit", 4) == 0)
		return (EXIT);
	else
		return (0);
}

// int	is_quote(char c)
// {
// 	if (c == '\'' )
// 		return (QUOTE);
// 	else if (c == '"')
// 		return (DOUBLE_QUOTE);
// 	else
// 		return (1);
// }

// int	is_operator(char *input)
// {
// 	int	i;

// 	i = 0;
// 	if (!input)
// 		return (0);
// 	while (input[i] != '\0')
// 	{
// 		if (input[i] == '>' && input[i + 1] == '>')
// 			return (DOUBLE_GREAT);
// 		else if (input[i] == '<' && input[i + 1] == '<')
// 			return (DOUBLE_LESS);
// 		else if (input[i] == '>' && input[i + 1] != '>')
// 			return (GREAT);
// 		else if (input[i] == '<' && input[i + 1] != '<')
// 			return (LESS);
// 		else if (input[i] == '|')
// 			return (PIPE);
// 		i++;
// 	}
// 	return (1);
// }

// /*is_operator(char *input): Checks if a string contains shell operators like '>>',
// 	'<<', '>', '<',
// 	'|'. It returns different constants depending on the operator.*/

// /* define if is random word, to use on tokenization later
// its possibel to return the word, but let this part out for now */

// int	is_word(const char *input)
// {
// 	int	i;

// 	i = 0;
// 	if (!input)
// 		return (0);
// 	while (input[i] != '\0' && ft_isalnum(input[i]))
// 	{
// 		while (input[i] != ' ' && input[i] != '\0')
// 			i++;
// 		return (WORD);
// 	}
// 	return (1);
// }

// /*is_word(const char *input): Checks if a string is a word (sequence of alphabetic characters). It returns a constant WORD if it is,
// 	and 1 otherwise.*/

// /* define if is argument, to use on tokenization later
// its possibel to return the arg, but let this part out for now */

// int	is_arg(const char *input)
// {
// 	int	i;

// 	i = 0;
// 	if (!input)
// 		return (0);
// 	while (input[i] != '\0')
// 	{
// 		if (input[i] == '-' && ft_isalpha(input[i + 1]) == 1)
// 		{
// 			while (input[i] != ' ' && input[i] != '\0')
// 				i++;
// 			return (ARG);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// /*is_arg(const char *input): Checks if a string is an argument (starts with '-' followed by alphabetic characters). It returns a constant ARG if it is,
// 	and 1 otherwise.*/

// /* thinking about do the same stuff to the commands bultins
// will write the functions, then we decide if is usefull to merge
// with the previous idea to make our token list*/

// int	is_builtin(char *input)
// {
// 	if (ft_strncmp(input, "echo", 4) == 0)
// 		return (ECHO);
// 	else if (ft_strncmp(input, "cd", 2) == 0)
// 		return (CD);
// 	else if (ft_strncmp(input, "pwd", 3) == 0)
// 		return (PWD);
// 	else if (ft_strncmp(input, "export", 6) == 0)
// 		return (EXPORT);
// 	else if (ft_strncmp(input, "unset", 5) == 0)
// 		return (UNSET);
// 	else if (ft_strncmp(input, "env", 3) == 0)
// 		return (ENV);
// 	else if (ft_strncmp(input, "exit", 4) == 0)
// 		return (EXIT);
// 	else
// 		return (1);
// }
/*is_builtin(char *input): Checks if a string is a shell built-in command like 'echo',
	'cd', 'pwd', 'export', 'unset', 'env',
	'exit'. It returns different constants depending on the command.*/

/* this function will be used to create the token list*/
