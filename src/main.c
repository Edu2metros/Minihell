/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:48:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/03 01:06:49 by  jaqribei        ###   ########.fr       */
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
		for (i = 0; i < cmd->count; i++)
			printf("%s ", cmd->args[i]);
		printf("\n");
		cmd = cmd->next;
	}
}

t_minishell	*get_control(void)
{
	static t_minishell	control;

	return (&control);
}

void	lstclear_cmd(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		i = 0;
		free(current->name);
		if (current->args != NULL)
		{
			while (current->args[i] != NULL)
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}
void	free_tokens(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (*token == NULL || (*token)->content == NULL)
		return ;
	current = *token;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	free_redirect_in(t_redirect_in **redirect)
{
	t_redirect_in	*current;
	t_redirect_in	*next;

	current = *redirect;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*redirect = NULL;
}

void	free_redirect_out(t_redirect_out **redirect)
{
	t_redirect_out	*current;
	t_redirect_out	*next;

	current = *redirect;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*redirect = NULL;
}

void    free_cmd(t_cmd **cmd)
{
    t_cmd   *current;
    t_cmd   *next;
    int     i;

    current = *cmd;
    while (current != NULL)
    {
        i = 0;
        next = current->next;
        free(current->name);
        while (current->args[i] != NULL)
        {
            free(current->args[i]);
            i++;
        }
        free(current->args);
        free(current);
        current = next;
    }
    *cmd = NULL;
}

void	free_all(t_minishell *minishell)
{
	free_tokens(&(minishell->token));
	free_redirect_in(&(minishell->redirect_list_in));
	free_redirect_out(&(minishell->redirect_list_out));
	free_cmd(&(minishell->cmd));
}

int	main(void)
{
	t_minishell	*mini;
	char		*input;
	t_token		*current_token;
	t_token		*next_token;
	t_cmd		*cmd = NULL;

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
			handle_redirects(mini);
			create_cmd_list(mini);
			test_built(mini->token, mini, mini->table);
		}
	}
	clear_history();
	free_all(mini);
	free(mini);
	free(input);
	return (0);
}
