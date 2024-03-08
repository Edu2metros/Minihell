/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:48:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/08 13:41:00 by eddos-sa         ###   ########.fr       */
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
			// printf("%i\n", mini->pipe->pipe_count);
			// handle_redirects(mini);
			create_cmd_list(mini);
			print_cmd_args(mini->cmd);
			hand_heredoc(mini);
			// if (mini->pipe->pipe_count > 0)
				// exec_pipe(mini);
			execution(mini->cmd, mini);
			close_fd(mini);
		}
	}
	clear_history();
	free_all(mini);
	free(input);
	return (0);
}
