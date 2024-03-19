/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:42:42 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/19 17:12:09 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	process_token_dollar(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;
	char	*tmp;

	tmp = NULL;
	start = i;
	if (input[i] == '?')
	{
		add_token(ft_itoa(mini->return_status), DOLLAR, 0, mini);
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
	free(tmp);
	free(substr);
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
