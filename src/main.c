/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:48:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/27 14:14:40 by eddos-sa         ###   ########.fr       */
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

void	print_cmd_args(t_cmd *cmd)
{
	int	i;

	if (cmd->args == NULL)
	{
		printf("No arguments.\n");
		return ;
	}
	while (cmd)
	{
		i = 0;
		while (cmd->args[i] != NULL)
		{
			printf("Argument %d: %s\n", i, cmd->args[i]);
			i++;
		}
		cmd = cmd->next;
	}
}

void	print_cmd_list(t_minishell *mini)
{
	int	i;

	t_cmd *cmd = mini->cmd; // Assuming the command list is stored in mini->cmd
	while (cmd)
	{
		printf("Command: %s\n", cmd->name);
		printf("Arguments: ");
		for (i = 0; i < cmd->count; i++)
		{
			printf("%s ", cmd->args[i]);
		}
		printf("\n");
		cmd = cmd->next;
	}
}

/* Leak arrumado, já que não tem algo que possa sair sem o ctrl + c,
 deixei para digitar "sair" que sai e não dá leak. */

t_minishell	*get_control(void)
{
	static t_minishell	control;

	return (&control);
}

void	lstclear_cmd(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

int	main(void)
{
	t_minishell	*mini;
	char		*input;
	t_token		*current_token;
	t_token		*next_token;
	t_cmd		*cmd;

	mini = ft_calloc(1, sizeof(t_minishell));
	while (1)
	{
		input = readline(PROMPT);
		if (!ft_strncmp(input, "quit", 5))
			break ;
		add_history(input);
		mini->token = NULL;
		if (validator(input))
		{
			tokenizer(input, mini);
			create_cmd_list(mini);
			test_built(mini->token, mini);
			current_token = mini->token;
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
	lstclear_cmd(&cmd);
	free(mini);
	return (0);
}
