/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:07:16 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/16 14:11:07 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		get_control()->return_status = 130;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit_signal(int sig) // Ctrl + '\'
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)", STDOUT_FILENO);
		get_control()->return_status = 131;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
	}
}

void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		get_control()->return_status = 0;
		free_all(get_control());
		exit(130);
	}
}

void	handle_sigint_child(int sig)
{
	if (sig == SIGINT)
	{
		get_control()->return_status = 130;
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void hand_signals()
{
	signal(SIGQUIT, handle_sigquit_signal);
	signal(SIGINT, handle_sigint);
}