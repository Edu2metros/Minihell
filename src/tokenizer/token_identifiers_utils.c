/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifiers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:54 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/13 22:54:30 by  jaqribei        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_token_arg(char *input, t_minishell *mini, int i)
{
	int		start;
	char	*substr;

	while (is_quote(input[i]))
		i++;
	start = i;
	while (input[i] && !is_quote(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, QUOTE, mini);
	while (is_quote(input[i]))
		i++;
	free(substr);
	return (i);
}

int	process_token_builtin(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != ' ' && input[i] != '\0' && !meta_char(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, is_builtin(substr), mini);
	free(substr);
	return (i);
}

int	process_token_word(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != ' ' && input[i] != '\0' && !meta_char(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, is_word(substr), mini);
	free(substr);
	return (i);
}

int	process_token_flag(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != '\0' && !my_isspace(input[i]) && !meta_char(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, is_flag(substr), mini);
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
	add_token(substr, type, mini);
	free(substr);
	return (i);
}
