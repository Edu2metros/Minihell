/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:29 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/13 22:56:35 by  jaqribei        ###   ########.fr       */
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
			// i = process_token_arg(input, mini, i);
			i = process_token_word(input, mini, i, start);
		else if (is_builtin(input + i))
			i = process_token_word(input, mini, i, start);
			// i = process_token_builtin(input, mini, i, start);
		else if (is_word(input + i))
			i = process_token_word(input, mini, i, start);
		else if (is_flag(input + i))
			// i = process_token_flag(input, mini, i, start);
			i = process_token_word(input, mini, i, start);
		else if (is_operator(input[i], input[i + 1]))
			i = process_token_operator(input, mini, i, start);
		else if (input[i] == '$') // extract $variable inside quote maybe?
			i = process_token_dollar(input, mini, i + 1, start);
		else
			i++;
		start = i;
	}
}

// int is_redirect (t_minishell *mini)
// {
// 	int	type;
	
// 	type = mini->token->type;

// 	if (type == 1 || type == 2 || || type == 6 || type == 7)
// 		return (type);
// 	return (0);
// }

// int	redirect_or_pipe(t_minishell *mini)
// {
// 	t_token	*token;
// 	int		type;
// 	int		prev_type;

// 	type = token->type;
// 	if (!(type == 3 || is_redirect(type)))
// 		return (0);
// 	if (token->previous)
// 		prev_type = token->type;
// 	else
// 		prev_type = -1;
// 	if (prev_type == -1 && !is_redirect(type))
// 		ft_putstr("Invalid token begining the line");
// 	else if (!token->next)
// 		ft_putstr("Invalid token at the end of the line");
// 	else if (!is_redirect(type)
// 		&& (is_redirect(prev_type) || prev_type == 3))
// 		ft_putstr("Invalid syntax");
// 	else
// 		return (0);
// 	return (1);
// }

// int	grammar_checker(t_minishell *mini)
// {
// 	t_token	*token;

// 	token = mini->token;
// 	if (!token)
// 		return (0);
// 	while (token)
// 	{
// 		if (redirect_or_pipe_or_pipe(token))
// 			return (1);
// 		token = token->next;
// 	}
// 	return (0);
// }