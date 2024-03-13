/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_signals_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:56:11 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/12 22:32:48 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_here(t_minishell *mini) // : Ignores the SIGINT signal and sets the signals flag to 0.
{
	// get_control()->signals = 0;
	signal(SIGINT, sig_here);
}

void	sig_handler(int sig) //  Handles the SIGINT signal by printing a newline character, resetting the Readline library, and clearing the current line.
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	hand_signals(t_minishell *mini) //Sets up signal handlers for SIGINT and SIGQUIT, calling sig_handler for SIGINT and ignoring SIGQUIT.
{
	get_control()->signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
// Compare this snippet from src/redirects/heredoc.c:

void	handle_control_d(char *input, t_hash_table *table) //  Handles the control-d signal by printing a newline character, resetting the Readline library, and clearing the current line.
{
	if (input == NULL)
	{
		free_table(&table);
		ft_putstr_fd("exit\n", 2);
		// close(get_control()->cmd->redirect_list_in->fd_in);
		// close(get_control()->cmd->redirect_list_out->fd_out);
		exit(0);
	}
}

void    ctrl_c_child(int sig)
{
    if (sig == SIGINT)
    {
        get_control()->return_status = 130;
        ft_putchar_fd('\n', STDOUT_FILENO);
    }
}
