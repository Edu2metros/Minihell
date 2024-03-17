/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:20:21 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/17 12:29:33 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "minishell: pwd error\n");
		get_control()->return_status = 1;
	}
	get_control()->return_status = 0;
	free(pwd);
	if(get_control()->cmd->on_fork == 1)
		exit(get_control()->return_status);
}
