/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:42:42 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/01 10:49:14 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Process when you have the '$' token
// but I have a doubt, what would be the limit? space?

#include "../../include/minishell.h"

int	process_token_dollar(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != '\0' && !my_isspace(input[i]) && !meta_char(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, DOLLAR, mini);
	return (i);
}

void	add_token(char *str, int type, t_minishell *mini)
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
	{
		return ;
	}
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
