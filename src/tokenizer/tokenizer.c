/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:44:29 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/21 17:11:54 by jaqribei         ###   ########.fr       */
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

// #include "../../include/minishell.h"

// void    create_cmd(t_minishell *mini)
// {
//     t_token    *token;

//     token = mini->token;
//     if (mini->cmd == NULL)
//         return ;
//     while (token != NULL)
//     {
//         if (!mini->cmd)
//             mini->cmd = ft_calloc(1, sizeof(t_cmd));
//         cmd_add_node(token, mini);
//         mini->cmd->next = ft_calloc(1, sizeof(t_cmd));
//         mini->cmd = mini->cmd->next;
//         token = token->next;
//     }
// }

// void parser(t_token *token, t_minishell *mini)
// {
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	j = 0;
// 	while (token != NULL)
// 	{
// 		if (token->type == WORD && is_builtin(token->content) < 0)
// 		{
// 			while (token->type != OUTPUT && token->type != PIPE && token->type != INPUT && token->type != APPEND && token->type != HEREDOC)
// 			{
// 				mini->cmd->args[i][j] = ft_strdup(token->content);
// 				token = token->next;
// 				j++;
// 			}	
// 			j = 0;
// 			// mini->cmd->name = token->content;
// 			// mini->cmd->type = token->type;
// 		}
// 		else if (token->type == WORD && access(token->content, F_OK) == -1)
// 		{
// 			while (token->type != OUTPUT && token->type != PIPE && token->type != INPUT && token->type != APPEND && token->type != HEREDOC)
// 			{
// 				mini->cmd->args[i][j] = ft_strdup(token->content);
// 				j++;
// 			}	
// 			j = 0;
// 			// mini->cmd->type = token->type;
// 			// mini->cmd->name = token->content;
// 		}
// 		else if (token->type == WORD)
// 		{
// 			while (token->type != OUTPUT && token->type != PIPE && token->type != INPUT && token->type != APPEND && token->type != HEREDOC)
// 			{
// 				mini->cmd->args[i][j] = ft_strdup(token->content);
// 				token = token->next;
// 				j++;
// 			}	
// 			j = 0;
// 			// mini->cmd->type = token->type;
// 			// mini->cmd->name = token->content;
// 		}
// 		// else if (token->type == PIPE)
// 		// {
// 		// 	mini->cmd->type = token->type;
// 		// 	mini->cmd->name = token->content;
// 		// }
// 	i++;
// 	}
// }