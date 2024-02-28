/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:20:21 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/28 19:29:06 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//function to show the current directory
// Need to make the command list and rewiew the implementation of the pwd command

void	ft_pwd(t_minishell *mini)
{
	char	*pwd;
	
	// mini->token->type = PWD;
	pwd = getcwd(NULL, 0);
	if(pwd)
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("error", 1);
	free(pwd);
}