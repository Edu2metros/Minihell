/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:56 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/04 13:59:33 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/* 
Etapas:
Lidar com Ctrl + C;
Pegar o que foi enviado e mandar pra args (?)
*/

void hand_heredoc(t_cmd *cmd)
{
	t_cmd *aux;
	char *input;
	int i;
	i = 0;
	while(!ft_strcmp(cmd->args[i], "<<"))
		i++;
	printf("%s\n", cmd->args[i + 1]);
	cmd->fd = open("/tmp/.Heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while(1)
	{
		input = readline(HEREDOC_PROMPT);
		if(!input || !ft_strcmp(input, cmd->args[i + 1]))
			break;
		ft_putendl_fd(input, cmd->fd);
		free(input);
	}
	free(input);
}
