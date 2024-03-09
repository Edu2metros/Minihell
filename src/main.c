/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:48:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/09 17:08:42 by jaqribei         ###   ########.fr       */
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

 	ft_bzero(get_control(), sizeof(t_minishell));
	mini = get_control();
	mini->pipe = ft_calloc(1, sizeof(t_pipe));
	mini->pipe->pipe_count = 0;
	mini->table = hash_population(mini, &mini->table);
	// mini->fd_in = dup(STDIN_FILENO);
	// mini->fd_out = dup(STDOUT_FILENO);
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
			// handle_redirects(mini);
			create_cmd_list(mini);
			pipes(mini, lst_first(mini->cmd));
			// minishell(mini);
			// close_fd(mini);
		}
	}
	clear_history();
	free_all(mini);
	free(input);
	return (0);
}
