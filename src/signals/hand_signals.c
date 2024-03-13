/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:07:16 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/12 22:32:35 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int sig) //ctrl + c
{
	if(sig == SIGINT)
	{
		get_control()->return_status = 130;
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
	}
}

void    sigquit_handler(int sig)  
{
    if (sig == SIGQUIT)
    {
        ft_putstr_fd("Quit (core dumped)", STDOUT_FILENO);
        get_control()->return_status = 131;
        ft_putchar_fd('\n', STDOUT_FILENO);
        rl_replace_line("", 0);
	}
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
		close_fd(get_control()); //verify later
		free(get_control());
		free_table(&get_control()->table);
		exit(130);
	}
}
