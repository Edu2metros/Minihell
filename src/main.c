/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:48:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/17 19:27:32 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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


void print_args_list(t_cmd *cmd) {
    int i = 0;
	
    printf("Command: %s\n", cmd->name);
    printf("Arguments:\n");
    while (cmd->args[i]) {
        printf("%s\n", cmd->args[i]);
        i++;
    }
}


/* Leak arrumado, já que não tem algo que possa sair sem o ctrl + c,
 deixei para digitar "sair" que sai e não dá leak. */

int	main(void)
{
	t_minishell	mini;
	char		*input;
	t_token		*current_token;
	t_token		*next_token;

	while (1)
	{
		input = readline(PROMPT);
		if (!ft_strncmp(input, "quit", 5))
			break ;
		add_history(input);
		mini.token = NULL;
		if (validator(input))
		{
			tokenizer(input, &mini);
			print_tokens(&mini);
			create_cmd_list(&mini);
			print_args_list(mini.cmd);
			test_built(mini.token, &mini);
			current_token = mini.token;
			while (current_token != NULL)
			{
				next_token = current_token->next;
				free(current_token->content);
				free(current_token);
				current_token = next_token;
			}
		}
	}
	clear_history();
	return (0);
}
