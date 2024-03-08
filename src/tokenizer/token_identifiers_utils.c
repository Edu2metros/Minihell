/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifiers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:54 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/07 20:56:00 by eddos-sa         ###   ########.fr       */
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

void	remove_quote(char *substr)
{
	int		i;
	char	quote;
	char	double_quote;
	char	*new_str;

	i = 0;
	quote = '\0';
	double_quote = '\0';
	new_str = ft_strdup("");
	while (substr[i])
	{
		if(substr[i] == '\'')
		{
			quote = substr[i];
			i++;
			while(substr[i] && substr[i] != quote)
			{
				new_str = ft_strjoin_char(new_str, substr[i]);
				i++;
			}
			i++;
			quote = '\0';
		}
		if(substr[i] == '"')
		{
			double_quote = substr[i];
			i++;
			while(substr[i] && substr[i] != double_quote)
			{
				new_str = ft_strjoin_char(new_str, substr[i]);
				i++;
			}
			i++;
			double_quote = '\0';
		}
		else
		{
			new_str = ft_strjoin_char(new_str, substr[i]);
			i++;
		}
	}
	ft_strlcpy(substr, new_str, ft_strlen(new_str) + 1);
	free(new_str);
}

/* void	remove_quote(char *substr)
{
	int		i;
	char	quote;
	char	double_quote;
	char	*new_str;

	i = 0;
	quote = '\0';
	double_quote = '\0';
	new_str = ft_strdup("");
	while (substr[i])
	{
		if (is_quote(substr[i]))
		{
			quote = substr[i];
			while (substr[i] && substr[i++] != quote)
				new_str = ft_strjoin_char(new_str, substr[i]);
			if (substr[i] == quote)
				i++;
		}
		else
		{
			new_str = ft_strjoin_char(new_str, substr[i]);
			i++;
		}
	}
	ft_strlcpy(substr, new_str, ft_strlen(new_str) + 1);
	free(new_str);
} */

char	*expand_variable_word(char *input, t_minishell *mini)
{
	int		i;
	int		start;
	char	*substr;
	char	*result;
	char quote;
	quote = '\0';
	result = ft_strdup("");
	i = 0;
	while (input[i] != '\0')
	{
		if(input[i] == '\'')
		{
			if(quote != '\0')
				quote = '\0';
			else
				quote = input[i];
		}
		if (input[i] == '$' && quote != '\'')
		{
			i++;
			start = i;
			while (ft_isalnum(input[i]) || input[i] == '_')
				i++;
			substr = ft_substr(input, start, i - start);
			if(getenv(substr))
				result = ft_strjoin(result, getenv(substr));
			else
			{
				if(hash_search(mini->table, substr))
					result = ft_strjoin(result, hash_search(mini->table, substr));
				else
					result = ft_strjoin(input, "");
			}
			free(substr);
		}
		else
		{
			result = ft_strjoin_char(result, input[i]);
			i++;
		}
	}
	free(input);
	return (result);
}

int	process_token_word(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != ' ' && input[i] != '\0' && !meta_char(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	substr = expand_variable_word(substr, mini);
	remove_quote(substr);
	add_token(substr, is_word(substr), 0, mini);
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
	if(type == PIPE)
		mini->pipe->pipe_count++;
	while (is_operator(input[i], input[i + 1]) && !ft_isalpha(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, type, 0, mini);
	free(substr);
	return (i);
}
