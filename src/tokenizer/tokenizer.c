/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:29 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/20 17:39:47 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_token_quote(char *input, t_minishell *mini, int i, int start)
{
	int		type;
	char	*substr;

	type = input[i];
	i++;
	while (input[i] != '\0' && input[i] != type)
		i++;
	substr = ft_substr(input, start, i - start + 1);
	if (ft_strncmp(substr, "''", 3) == 0 || ft_strncmp(substr, "\"\"", 3) == 0)
	{
		free(substr);
		return (i + 1);
	}
	if (my_isspace(input[i + 1]))
		add_token(substr, QUOTE, 1, mini);
	else
		add_token(substr, QUOTE, 0, mini);
	free(substr);
	return (i + 1);
}

void	tokenizer(char *input, t_minishell *mini)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (input[i] != '\0')
	{
		if (is_quote(input[i]))
			i = process_token_quote(input, mini, i, start);
		else if (is_flag(input + i))
			i = process_token_word(input, mini, i, start);
		else if (is_operator(input[i], input[i + 1]))
			i = process_token_operator(input, mini, i, start);
		else if (input[i] == '$')
			i = process_token_dollar(input, mini, i + 1, start);
		else if (is_builtin(input + i))
			i = process_token_word(input, mini, i, start);
		else if (is_word(input + i))
			i = process_token_word(input, mini, i, start);
		else
			i++;
		start = i;
	}
}

int	lstsize(t_token *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

void	add_token_space(char *input, int i)
{
	char	*status_str;

	status_str = ft_itoa(get_control()->return_status);
	if (input[i + 1] != '\0' && my_isspace(input[i]))
		add_token(status_str, DOLLAR, 1, get_control());
	else
		add_token(status_str, DOLLAR, 0, get_control());
	free(status_str);
}
