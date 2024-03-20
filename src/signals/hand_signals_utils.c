/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_signals_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:56:11 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/20 10:47:45 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_control_d(char *input, t_hash_table *table)
{
	if (input == NULL)
	{
		free_table(&table);
		free_all(get_control());
		close_fd();
		clear_history();
		ft_putstr_fd("exit\n", 2);
		exit(get_control()->return_status);
	}
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	hand_signals()
{
	signal(SIGQUIT, handle_sigquit_signal);
	signal(SIGINT, handle_sigint);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, handle_sigquit_signal);
}
