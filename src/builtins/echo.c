/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:57:02 by  jaqribei         #+#    #+#             */
/*   Updated: 2024/02/11 23:58:20 by  jaqribei        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// mimics the behavior of the echo command in a Unix shell.
// Need to make the command list and rewiew the implementation of the echo command

void	ft_echo(t_minishell *mini)
{
	int		n_flag;
	int		i;
	char	**args;

	args = mini->cmd->args;
	n_flag = 0;
	i = 0;
	if (!args)
		ft_putstr_fd("\n", 1);
	else
	{
		while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
		{
			n_flag = 1;
			i++;
		}
		while (args[i] != NULL)
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if(n_flag == 0)
		ft_putstr_fd("\n", 1);
}
