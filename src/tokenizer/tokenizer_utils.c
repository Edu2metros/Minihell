/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:42:42 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/20 14:00:56 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token_dolar(char *tmp, char *substr)
{
	if (tmp != NULL)
		free(tmp);
	if (substr != NULL)
		free(substr);
}

int	process_token_dollar(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;
	char	*tmp;

	tmp = NULL;
	start = i;
	if (input[i] == '?')
	{
		add_token_space(input, i);
		return (i + 1);
	}
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	substr = ft_substr(input, start, i - start);
	tmp = hash_search(mini->table, substr);
	if (ft_strlen(substr) == 0)
		tmp = ft_strdup("$");
	if (tmp != NULL)
	{
		if (input[i] != '\0' && my_isspace(input[i]))
			add_token(tmp, DOLLAR, 1, mini);
		else
			add_token(tmp, DOLLAR, 0, mini);
	}
	free_token_dolar(tmp, substr);
	return (i);
}

void	add_token(char *str, int type, int space, t_minishell *mini)
{
	t_token	*new_token;
	t_token	*last_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		exit(EXIT_FAILURE);
	new_token->content = ft_strdup(str);
	new_token->type = type;
	new_token->next = NULL;
	new_token->previous = NULL;
	new_token->space = space;
	if (mini->token)
	{
		last_token = mini->token;
		while (last_token->next != NULL)
			last_token = last_token->next;
		new_token->previous = last_token;
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

void	lstclear_token(t_token *lst)
{
	t_token	*current;
	t_token	*next;

	if (lst == NULL)
		return ;
	current = lst;
	while (current->previous != NULL)
		current = current->previous;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}
