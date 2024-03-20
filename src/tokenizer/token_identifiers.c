/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:46 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/20 10:35:58 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator(char chr1, char chr2)
{
	if (!chr1)
		return (0);
	if (chr1 == '>' && chr2 == '>')
		return (APPEND);
	else if (chr1 == '<' && chr2 == '<')
		return (HEREDOC);
	else if (chr1 == '>' && chr2 != '>')
		return (OUTPUT);
	else if (chr1 == '<' && chr2 != '<')
		return (INPUT);
	else if (chr1 == '|')
		return (PIPE);
	else if (!ft_isalnum(chr1) && !my_isspace(chr1) && !is_excession(chr1))
		return (OTHER);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\0' || c == 0)
		return (0);
	if (c == '\'')
		return (QUOTE);
	else if (c == '"')
		return (DOUBLE_QUOTE);
	else
		return (0);
}

int	is_word(const char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0' && (ft_isalnum(input[i]) || alpha_num(input[i])
			|| is_quote(input[i]) || input[i] == '='))
	{
		while (!my_isspace(input[i]) && input[i] != '\0')
			i++;
		return (WORD);
	}
	return (0);
}

int	is_flag(const char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0')
	{
		if (input[i] == '-' && ft_isalpha(input[i + 1]) && i == 0)
		{
			while (input[i] != ' ' && input[i] != '\0')
				i++;
			return (WORD);
		}
		i++;
	}
	return (0);
}

char	*expand_val(char *input, int *i, t_minishell *mini, char *result)
{
	char	*substr;
	int		start;

	(*i)++;
	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	substr = ft_substr(input, start, *i - start);
	if (hash_search(mini->table, substr) != NULL)
		result = ft_strjoin(result, hash_search(mini->table, substr));
	else
		result = ft_strjoin(result, "");
	free(substr);
	return (result);
}
