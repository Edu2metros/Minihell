/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:29 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/29 15:49:49 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tokenizer(char *input, t_minishell *mini)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (input[i] != '\0')
	{
		if (is_quote(input[i]))
			i = process_token_word(input, mini, i, start);
		else if (is_builtin(input + i))
			i = process_token_word(input, mini, i, start);
		else if (is_word(input + i))
			i = process_token_word(input, mini, i, start);
		else if (is_flag(input + i))
			i = process_token_word(input, mini, i, start);
		else if (is_operator(input[i], input[i + 1]))
			i = process_token_operator(input, mini, i, start);
		else if (input[i] == '$')
			i = process_token_dollar(input, mini, i + 1, start);
		else
			i++;
		start = i;
	}
}
