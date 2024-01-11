/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:55:41 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/11 18:54:26 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_new_token(char *content, int type)
{
	t_token	*ptr;

	ptr = malloc(sizeof(t_token));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->type = type;
	ptr->next = NULL;
	return (ptr);
}

t_token	*add_node(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_token(char *str, int type, t_minishell *mini)
{
	t_token	*new_token;
	t_token	*last_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit(EXIT_FAILURE);
	if (ft_strlen(str) == 2)
		new_token->content = ft_strdup(str);
	else
		new_token->content = str;
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

int	check_meta(const char *input, t_minishell *mini)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
		{	
			add_token(">>", DOUBLE_GREAT, mini);
			i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token("<<", DOUBLE_LESS, mini);
			i++;
		}
		else if (input[i] == '>' && input[i + 1] != '>')
			add_token(">", GREAT, mini);
		else if (input[i] == '<' && input[i + 1] != '<')
			add_token("<", LESS, mini);
		else if (input[i] == '|')
			add_token("|", PIPE, mini);
		else if (input[i] == '\'')
			add_token("'", QUOTE, mini);
		else if (input[i] == '\"')
			add_token("\"", DOUBLE_QUOTE, mini);
		i++;
	}
	return (1);
}

int	validate_input(const char *token, char **envp, t_minishell *mini)
{
	if (check_meta(token, mini) == 0)
		return (0);
	return (1);
}