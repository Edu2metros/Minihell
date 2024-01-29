/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:29 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/29 17:11:27 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenizer(char *input, t_minishell *mini)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (input[i] != '\0')
	{
		if (is_quote(input[i]))
			i = process_token_quote(input, mini, i);
		else if (is_builtin(input + i))
			i = process_token_builtin(input, mini, i, start);
		else if (is_word(input + i))
			i = process_token_word(input, mini, i, start);
		else if (is_arg(input + i))
			i = process_token_arg(input, mini, i, start);
		else if (is_operator(input[i], input[i + 1]))
			i = process_token_operator(input, mini, i, start);
		else if (input[i] == '$')
			i = process_token_dollar(input, mini, i + 1, start);
		else
			i++;
		start = i;
	}
}

void	add_token(char *str, int type, t_minishell *mini)
{
	t_token	*new_token;
	t_token	*last_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit(EXIT_FAILURE);
	new_token->content = ft_strdup(str);
	new_token->type = type;
	new_token->next = NULL;
	if (mini->token)
	{
		last_token = mini->token;
		while (last_token->next != NULL)
			last_token = last_token->next;
		last_token->next = new_token;
	}
	else
		mini->token = new_token;
}

void	print_tokens(t_minishell *mini)
{
	t_token	*current_token;

	current_token = mini->token;
	while (current_token != NULL)
	{
		printf("Token: %s: Type: %d\n\n", current_token->content,
			current_token->type);
		current_token = current_token->next;
	}
}

int	main(void)
{
	t_minishell	mini;
	char		*input;
	t_token		*current_token;
	t_token		*next_token;

	while (1)
	{
		input = readline("");
		if (!ft_strncmp(input, "exit", 5))
			break ;
		add_history(input);
		mini.token = NULL;
		tokenizer(input, &mini);
		print_tokens(&mini);
		current_token = mini.token;
		while (current_token != NULL)
		{
			next_token = current_token->next;
			free(current_token->content);
			free(current_token);
			current_token = next_token;
		}
	}
	clear_history();
	return (0);
}
