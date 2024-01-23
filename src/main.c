/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:48:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/18 15:16:10 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	add_token(char *str, int type, t_minishell *mini)
// {
// 	t_token	*new_token;
// 	t_token	*last_token;

// 	new_token = malloc(sizeof(t_token));
// 	if (!new_token)
// 		exit(EXIT_FAILURE);
// 	if (ft_strlen(str) == 2)
// 		new_token->content = ft_strdup(str);
// 	else
// 		new_token->content = str;
// 	new_token->type = type;
// 	new_token->next = NULL;
// 	if (mini->token)
// 	{
// 		last_token = mini->token;
// 		while (last_token->next != NULL)
// 			last_token = last_token->next;
// 		last_token->next = new_token;
// 	}
// 	else
// 		mini->token = new_token;
// }

// int	check_meta(char *input, t_minishell *mini)
// {
// 	int	i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '>' && input[i + 1] == '>')
// 		{
// 			add_token(">>", DOUBLE_GREAT, mini);
// 			i++;
// 		}
// 		else if (input[i] == '<' && input[i + 1] == '<')
// 		{
// 			add_token("<<", DOUBLE_LESS, mini);
// 			i++;
// 		}
// 		else if (input[i] == '>' && input[i + 1] != '>')
// 			add_token(">", GREAT, mini);
// 		else if (input[i] == '<' && input[i + 1] != '<')
// 			add_token("<", LESS, mini);
// 		else if (input[i] == '|')
// 			add_token("|", PIPE, mini);
// 		i++;
// 	}
// 	return (1);
// }
int is_quote(char c)
{
    return(c == '\'' || c == '"');
}

void word(char **str, t_token *token, int *i)
{
    if (*str == NULL || **str == '\0' || is_quote(**str))
        return;
    if(token->args == NULL)
        token->args[*i]= ft_strdup("");
    while (**str != '\0' && !meta_char(**str) && **str != '-')
    {
        char single_char_str[2] = {**str, '\0'};
        token->args[*i] = ft_strjoin(token->args[*i], single_char_str);
        (*str)++;
    }
    token->args[*i] = '\0';
    (*i)++;
}

void meta(char **str, t_token *token, int *i)
{
    if (*str == NULL || **str == '\0' || is_quote(**str))
        return;
    if(token->args == NULL)
        token->args[*i]= ft_strdup("");
    if (meta_char(**str) && (**str == '"' || **str == '\''))
    {
        // char single_char_str[2] = {**str, '\0'};
        if (**str == '>' && *(*str + 1) == '>')
            token->args[*i] = ft_strjoin(token->args[*i], ">>");
        else if (**str == '>' && *(*str + 1) != '>')
            token->args[*i] = ft_strjoin(token->args[*i], ">");
        else if (**str == '|')
            token->args[*i] = ft_strjoin(token->args[*i], "|");
        else if (**str == '<' && *(*str + 1) == '<')
            token->args[*i] = ft_strjoin(token->args[*i], "<<");
        else if (**str == '<' && *(*str + 1) != '<')
            token->args[*i] = ft_strjoin(token->args[*i], "<");
        else
            printf("precisa ter msg de erro aq?\n");

        if (token->args[*i] == NULL)
            return;
        else if (ft_strlen(token->args[*i]) == 2)
            (*str) += 2;
        else
            (*str)++;
        token->args[*i] = '\0';
        (*i)++;
    }
}

void quote(char **str, t_token *token, int *i)
{
    if (!is_quote(**str))
        return;
    if(token->args == NULL)
        token->args[*i]= ft_strdup("");
    while (is_quote(**str))
        (*str)++;

    while (!is_quote(**str))
    {
        char single_char_str[2] = {**str, '\0'};
        token->args[*i] = ft_strjoin(token->args[*i], single_char_str);
        (*str)++;
    }

    while (is_quote(**str))
        (*str)++;
    token->args[*i] = '\0';
    (*i)++;
}

void flag(char **str, t_token *token, int *i)
{
    if (*str == NULL || **str == '\0' || is_quote(**str) || meta_char(**str))
        return;
    if(token->args == NULL)
        token->args[*i]= ft_strdup("");
    if (**str == '-')
    {
        while (**str != '\0' && !meta_char(**str) && !is_quote(**str) && !my_isspace(**str))
        {
            char single_char_str[2] = {**str, '\0'};
            token->args[*i] = ft_strjoin(token->args[*i], single_char_str);
            (*str)++;
        }
    }
    token->args[*i] = '\0';
    (*i)++;
}

void tokenizer(char *str, t_minishell *mini)
{
    int i = 0;
    mini->token->args = (char **)ft_calloc(1, sizeof(char *));

    while (*str)
    {
        while (my_isspace(*str))
            str++;

        word(&str, mini->token, &i);
        meta(&str, mini->token, &i);
        quote(&str, mini->token, &i);
        flag(&str, mini->token, &i);
    }

    int j = 0;
    while (j < i)
    {
        printf("%s\n", mini->token->args[j]);
        j++;
    }
}

/* 
Separar na split por espaço
split diferenciada, 
 */

int	main(void)
{
	char		*prompt;
	t_minishell	*mini;

	mini = ft_calloc(1, sizeof(t_minishell));
	mini->token = ft_calloc(1, sizeof(t_token));
	while (1)
	{
		prompt = readline("Minishell $> ");
		add_history(prompt);
		validator(prompt);
	}
	clear_history();
}

// lexer(prompt, mini);