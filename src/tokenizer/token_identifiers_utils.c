/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifiers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:54 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/20 10:35:07 by eddos-sa         ###   ########.fr       */
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
	add_token(substr, QUOTE, 0, mini);
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
	add_token(substr, is_builtin(substr), 0, mini);
	free(substr);
	return (i);
}

void	handle_single_quote(char *substr, char **new_str, int *i)
{
	char	quote;

	quote = substr[*i];
	(*i)++;
	while (substr[*i] && substr[*i] != quote)
	{
		*new_str = ft_strjoin_char(*new_str, substr[*i]);
		(*i)++;
	}
	(*i)++;
}

void	handle_double_quote(char *substr, char **new_str, int *i)
{
	char	double_quote;

	double_quote = substr[*i];
	(*i)++;
	while (substr[*i] && substr[*i] != double_quote)
	{
		*new_str = ft_strjoin_char(*new_str, substr[*i]);
		(*i)++;
	}
	(*i)++;
}

void	remove_quote(char *substr)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strdup("");
	while (substr[i])
	{
		if (substr[i] == '\'')
			handle_single_quote(substr, &new_str, &i);
		else if (substr[i] == '"')
			handle_double_quote(substr, &new_str, &i);
		else
		{
			new_str = ft_strjoin_char(new_str, substr[i]);
			i++;
		}
	}
	ft_strlcpy(substr, new_str, ft_strlen(new_str) + 1);
	free(new_str);
}
