/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:01 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/04 12:49:19 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void execution(t_cmd *cmd)
{
	char **path;
	char *tmp;
	int i;

	path = ft_split(getenv("PATH"), ':');
	i = 0;
	pid_t pid = fork();
	
	while (path[i] != NULL && !pid)
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, cmd->name);
		if(cmd->fd)
		{
			dup2(cmd->fd, 0);
			close(cmd->fd);
		}
		if (access(tmp, F_OK) == 0)
		{
			execve(tmp, cmd->args, NULL);
			break;
		}
		i++;
		free(tmp);
	}
	if (pid)
		waitpid(pid, NULL, 0);
}

void	test_built(t_token *token, t_minishell *mini)
{
	int	i;
	int	j;
	t_hash_table		*table;
	t_cmd *aux;
	aux = mini->cmd;
	i = 0;
	j = 0;
	table = hash_population(mini, &table);
	
	while (mini->cmd != NULL)
	{
		while(aux->next)
		{
			if(aux->type == HEREDOC)
				hand_heredoc(aux);
			aux = aux->next;
		}
		if (mini->cmd->type == WORD)
		{
			if (is_builtin(mini->cmd->name) == PWD)
				ft_pwd();
			if (is_builtin(mini->cmd->name) == ECHO)
				ft_echo(mini->cmd);
			if (is_builtin(mini->cmd->name) == CD)
				hand_cd(mini->cmd);
			if (is_builtin(mini->cmd->name) == ENV)
				env(mini->cmd, &table);
			else
				execution(mini->cmd);
		}
		mini->cmd = mini->cmd->next;
	}
}
