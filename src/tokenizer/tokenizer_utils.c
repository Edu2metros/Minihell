/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:42:42 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/17 19:41:00 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Process when you have the '$' token
// but I have a doubt, what would be the limit? space?

#include "../../include/minishell.h"

int	process_token_dollar(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != '\0' && ft_isalpha(input[i]))
		i++;
	substr = ft_substr(input, start, i);
	add_token(substr, DOLLAR, mini);
	return (i);
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

void	free_token(t_minishell *mini)
{
	t_token	*token;
	t_token	*aux;

	token = mini->token;
	while (token != NULL)
	{
		aux = token->next;
		free(token->content);
		free(token);
		token = aux;
	}
	mini->token = NULL;
}

int	token_list_size(t_token *token, t_minishell *mini)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD && token->previous->type != is_redirect(mini))
			count++;
		token = token->next;
	}
	return (count);
}