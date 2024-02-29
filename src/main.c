/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:48:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/29 17:16:30 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	*get_control(void)
{
	static t_minishell	control;

	return (&control);
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
		}
	}
	clear_history();
	free_all(mini);
	free(mini);
	free(input);
	return (0);
}
