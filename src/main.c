/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:48:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/14 18:11:35 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	*get_control(void)
{
	static t_minishell	control;

	return (&control);
}

void	pipe_or_not(t_minishell *mini, t_cmd *cmd)
{
	if (cmd->next == NULL)
		exec_command(cmd, mini);
	else
		exec_pipe(mini, cmd);
}

static void	minishell(t_minishell *mini, t_hash_table *table)
{
	char	*input;
	
	while (TRUE)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		get_control()->heredoc = 0;
		input = readline(PROMPT);
		handle_control_d(input, table);
		if (!ft_strncmp(input, "quit", 5))
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		add_history(input);
		if (validator(input))
		{
			tokenizer(input, mini);
			create_cmd_list(mini);
			get_heredoc();
			if (get_control()->heredoc)
				return ;
			pipe_or_not(mini, lst_first(mini->cmd));
			close_fd(mini);
		}
		free_all(mini);
	}
	clear_history();
	free(input);
}

int	main(void)
{
	t_minishell	*mini;
	ft_bzero(get_control(), sizeof(t_minishell));
	mini = get_control();
	mini->pipe = ft_calloc(1, sizeof(t_pipe));
	mini->pipe->pipe_count = 0;
	mini->table = hash_population(mini, &mini->table);
	minishell(mini, mini->table);
}
