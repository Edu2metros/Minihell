/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:29 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/14 14:08:23 by jaqribei         ###   ########.fr       */
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
		else if (input[i] == '$') // extract $variable inside quote maybe?
			i = process_token_dollar(input, mini, i + 1, start);
		else
			i++;
		start = i;
	}
}

// int is_redirect (t_minishell *mini, int	type)
// {
// 	type = mini->token->type;

// 	if (type == OUTPUT || type == INPUT || type == APPEND || type == HEREDOC)
// 		return (type);
// 	return (0);
// }

// int	redirect_or_pipe(t_minishell *mini)
// {
// 	t_token	*token;
// 	int		type;
// 	int		prev_type;

// 	type = token->type;
// 	if (!(type == 3 || is_redirect(mini, type)))
// 		return (0);
// 	if (token->previous)
// 		prev_type = token->type;
// 	else
// 		prev_type = -1;
// 	if (prev_type == -1 && !is_redirect(mini, type))
// 		ft_putstr("Invalid token begining the line");
// 	else if (!token->next)
// 		ft_putstr("Invalid token at the end of the line");
// 	else if (!is_redirect(mini, type)
// 		&& (is_redirect(mini, prev_type) || prev_type == 3))
// 		ft_putstr("Invalid syntax");
// 	else
// 		return (0);
// 	return (1);
// }

// void	parser(t_minishell *mini)
// {
// 	t_token	*token;

// 	token = mini->token;
// 	if (!token)
// 		return ;
// 	while (token)
// 	{
// 		if (redirect_or_pipe(mini))
// 			return ;
// 		token = token->next;
// 	}
// 	return ;
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/12 19:49:35 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    create_cmd(t_minishell *mini)
{
    t_token    *token;

    token = mini->token;
    if (mini->cmd == NULL)
        return ;
    while (token != NULL)
    {
        if (!mini->cmd)
            mini->cmd = ft_calloc(1, sizeof(t_cmd));
        cmd_add_node(token, mini);
        mini->cmd->next = ft_calloc(1, sizeof(t_cmd));
        mini->cmd = mini->cmd->next;
        token = token->next;
    }
}

void cmd_add_node(t_token *token, t_minishell *mini)
{
    if (token->type == WORD && is_builtin(token->content) < 0)
    {
        mini->cmd->name = token->content;
        mini->cmd->type = token->type;
    }
    else if (token->type == WORD && access(token->content, F_OK))
    {
        mini->cmd->type = token->type;
        mini->cmd->name = token->content;
    }
    else if (token->type == WORD)
    {
        mini->cmd->type = token->type;
        mini->cmd->name = token->content;
    }
    else if (token->type == PIPE)
    {
        mini->cmd->type = token->type;
        mini->cmd->name = token->content;
    }
}