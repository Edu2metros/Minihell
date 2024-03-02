/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:29 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/02 18:53:16 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Se a quantidade total de aspas for par levando o tipo de aspa da primeira passa
Ignora o mesmo tipo de aspa até achar algo que é != aspa
Dois levares, se for duplas vai pra um canto, se for simples vai pra outro canto
expande a variável assim que achar e se a primeira aspa encontrada for duplas
*/

int	process_token_quote(char *input, t_minishell *mini, int i, int start)
{
	int		type;
	char	*substr;

	type = is_quote(input[i]);
	i++;
	while (input[i] != '\0' && input[i] != type)
		i++;
	substr = ft_substr(input, start, i - start + 1);
	add_token(substr, QUOTE, mini);
	free(substr);
	return (i);
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
	print_tokens(mini);
}
