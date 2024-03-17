/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:57:02 by  jaqribei         #+#    #+#             */
/*   Updated: 2024/03/17 12:28:44 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strchr_flag(const char *s, int c)
{
	char	*s_copy;

	s_copy = (char *)s;
	if (ft_strncmp(s_copy, "-n", 2) == 0)
		s_copy++;
	else 
		return (0);
	while (*s_copy)
	{
		if (*s_copy != (char)c)
			return (0);
		s_copy++;
	}
	if (*s_copy == '\0')
		return (1);
	return (0);
}

void    ft_echo(t_cmd *cmd)
{
    int    n_flag;
    int    i;
    int    fd_out;

    i = 1;
    n_flag = 0;
    fd_out = 1;
	cmd->redirect_list_out = lstlast_out(cmd->redirect_list_out);
    if (cmd->redirect_list_out)
        fd_out = cmd->redirect_list_out->fd_out;
    if (!cmd->args[i])
        ft_putstr_fd("\n", fd_out);
    while (cmd->args[i] && ft_strchr_flag(cmd->args[i], 'n') == 1)
    {
        n_flag = 1;
        i++;
    }
    while (cmd->args[i] != NULL)
    {
        ft_putstr_fd(cmd->args[i], fd_out);
        if (cmd->args[i + 1] != NULL)
            ft_putstr_fd(" ", fd_out);
        i++;
    }
    if (n_flag == 0)
        ft_putstr_fd("\n", fd_out);
	get_control()->return_status = 0;
    if(cmd->on_fork == 1)
        exit(get_control()->return_status);
}

