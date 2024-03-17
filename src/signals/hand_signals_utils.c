/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_signals_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:56:11 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/17 16:53:09 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_control_d(char *input, t_hash_table *table)
{
	if (input == NULL)
	{
		free_table(&table);
		ft_putstr_fd("exit\n", 2);
		close(get_control()->cmd->redirect_list_in->fd_in);
		close(get_control()->cmd->redirect_list_out->fd_out);
		exit(0);
	}
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void hand_signals(t_minishell *mini)
{
	signal(SIGQUIT, handle_sigquit_signal);
	signal(SIGINT, handle_sigint);
}
