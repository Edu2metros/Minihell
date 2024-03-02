/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:57:02 by  jaqribei         #+#    #+#             */
/*   Updated: 2024/03/01 11:22:18 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* void	handle_dollar(t_cmd *cmd)
{
	int		i;
	char	*val;
	int		j;

	i = 0;
	j = 0;
	if(cmd->args[i][j] == '"')
	{
		while(cmd->args[i][j] != '$' && cmd->args[i][j] != '\0')
			j++;
		if(cmd->args[i][j] == '\0')
			return ;
	}
	else if(cmd->args[i][j] == '\'')
		return ;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '$')
		{
			val = ft_strdup(cmd->args[i]);
			free(cmd->args[i]);
			ft_memmove(val, val + 1, ft_strlen(val));
			if (getenv(val) != NULL)
				cmd->args[i] = ft_strdup(getenv(val));
			free(val);
		}
		i++;
	}
} */

/* void handle_quotes(t_cmd *cmd)
{
	int i;
	i = 0;
	while(cmd->args[i] != NULL)
	{

	}
} */

void	ft_echo(t_cmd *cmd)
{
	int	n_flag;
	int	i;

	printf("\n===================    ECHO    ===================\n\n");
	i = 1;
	cmd = lst_first(cmd);
	n_flag = 0;
	if (!cmd->args[i])
		ft_putstr_fd("\n", 1);
	while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", 1);
}
