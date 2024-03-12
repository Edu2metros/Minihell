/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:07:16 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/11 20:10:03 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    sigint_handler(int sig) //ctrl + c
{
	if(sig == SIGINT)
	{
		// get_control()->code_status = 130;
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
	}
}

void	sigquit_handler(int sig) // ctrl + '\'
{
	if(sig == SIGQUIT)
		ft_putstr_fd("Quit", 2);
}

void	sig_ignore(void) // this function is to ignore the signals
{
	// get_control()->signals = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_parent(void)  //Sets up signal handlers for SIGINT and SIGQUIT, calling 
{
	// get_control()->signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	sig_here(int sig) // Handles the SIGINT signal for a specific scenario, closing file descriptors, freeing memory, and exiting with a specific status code.
{
	ft_putstr("\n");
	if(sig == SIGINT)
	{
		// close_fd(get_control()); //verify later
		// free(get_control());
		// free_table(&get_control()->table);
		exit(130);
	}
}
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
	// get_control()->signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
// Compare this snippet from src/redirects/heredoc.c: