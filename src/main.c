/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:48:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/20 13:16:14 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	*get_control(void)
{
	static t_minishell	control;

	return (&control);
}

int	ft_isredirect(char *string)
{
	if (ft_strncmp(string, ">", 2) == 0 || ft_strncmp(string, ">>", 3) == 0
		|| ft_strncmp(string, "<", 2) == 0 || ft_strncmp(string, "<<", 3) == 0)
		return (1);
	return (0);
}

void	free_out_while(t_minishell *mini)
{
	free_all(mini);
	clear_history();
}

static void	minishell(t_minishell *mini, t_hash_table *table)
{
	char	*input;

	while (TRUE)
	{
		mini->cmd = NULL;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		get_control()->heredoc = 0;
		input = readline(PROMPT);
		handle_control_d(input, table);
		add_history(input);
		if (!validator(input))
			continue ;
		tokenizer(input, mini);
		create_cmd_list(mini);
		pipe_or_not(mini);
		if (mini->cmd)
		{
			free_redirect_out(&mini->cmd->redirect_list_out);
			free_redirect_in(&mini->cmd->redirect_list_in);
		}
		close_fd();
		free_all(mini);
	}
}

int	main(void)
{
	t_minishell	*mini;

	ft_bzero(get_control(), sizeof(t_minishell));
	mini = get_control();
	mini->table = hash_population(&mini->table);
	minishell(mini, mini->table);
	free_table(&mini->table);
	return (0);
}
