/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:33:44 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/29 15:59:57 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hand_cd(t_cmd *cmd)
{
	char	*pwd;
	char	*path;
	int		i;

	printf("\n===================    CD    ===================n\n");
	pwd = getcwd(NULL, 0);
	i = 1;
	if (!cmd->args[i])
		path = getenv("HOME");
	else
		path = cmd->args[i];
	if (chdir(path) != 0)
		handle_error(0);
	else
	{
		if (pwd != NULL)
			setenv("PWD", pwd, 1);
		else
			handle_error(0);
	}
}
