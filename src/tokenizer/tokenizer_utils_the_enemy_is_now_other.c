/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_the_enemy_is_now_other.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:32:53 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/20 10:34:58 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	update_quote(char quote, char current_char)
{
	if (current_char == '\'')
	{
		if (quote == '\'')
			return ('\0');
		else
			return ('\'');
	}
	return (quote);
}

int	process_token_word(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;
	int		in_quotes;

	in_quotes = 0;
	while (input[i] != '\0' && (in_quotes || (!meta_char(input[i])
				&& input[i] != ' ')))
	{
		if (input[i] == '"' || input[i] == '\'')
			in_quotes = !in_quotes;
		i++;
	}
	substr = ft_substr(input, start, i - start);
	substr = expand_variable_word(substr, mini);
	remove_quote(substr);
	add_token(substr, is_word(substr), 1, mini);
	free(substr);
	return (i);
}

int	process_token_flag(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != '\0' && !my_isspace(input[i]) && !meta_char(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, is_flag(substr), 0, mini);
	free(substr);
	return (i);
}

int	process_token_operator(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;
	int		type;

	type = is_operator(input[i], input[i + 1]);
	while (is_operator(input[i], input[i + 1]) && !ft_isalpha(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, type, 0, mini);
	free(substr);
	return (i);
}

char	*expand_variable_word(char *input, t_minishell *mini)
{
	int		i;
	char	*result;
	char	quote;

	quote = '\0';
	result = ft_strdup("");
	i = 0;
	while (input[i] != '\0')
	{
		quote = update_quote(quote, input[i]);
		if (input[i] == '$' && quote != '\'')
			result = expand_val(input, &i, mini, result);
		else
		{
			result = ft_strjoin_char(result, input[i]);
			i++;
		}
	}
	free(input);
	return (result);
}
