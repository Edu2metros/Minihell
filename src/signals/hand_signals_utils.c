/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_signals_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:56:11 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/14 18:22:59 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include "../../include/minishell.h"

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

