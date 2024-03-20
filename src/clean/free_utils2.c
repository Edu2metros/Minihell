/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:29:52 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/20 15:38:20 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_all_child(t_minishell *mini)
{
	free_tokens(&(mini->token));
	free_redirect_out(&(mini->redirect_list_out));
	free_redirect_in(&(mini->redirect_list_in));
	free_reds(mini->cmd);
	lstclear_cmd(&(mini->cmd));
	close_fd();
	clear_history();
	free_table(&mini->table);
}
