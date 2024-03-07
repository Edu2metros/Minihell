/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:01 by eddos-sa          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/03/07 13:36:53 by eddos-sa         ###   ########.fr       */
=======
/*   Updated: 2024/03/07 13:38:20 by jaqribei         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execution(t_cmd *cmd, t_minishell *mini)
{
	char	**path;
	char	*tmp;
	int		i;
	pid_t	pid;

	path = ft_split(getenv("PATH"), ':');
	i = 0;
	pid = fork();
	while (path[i] != NULL && !pid)
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, cmd->name);
		if (access(tmp, F_OK) == 0)
		{
			if (mini->redirect_list_out->fd_out)
				printf("%i\n", dup2(mini->redirect_list_out->fd_out, 1));
			// if (mini->redirect_list_in->fd_in)
			// 	printf("%i\n", dup2(mini->redirect_list_in->fd_in, 1));
			execve(tmp, cmd->args, NULL);
			break ;
		}
		i++;
		free(tmp);
	}
	if (pid)
		waitpid(pid, NULL, 0);
	// kill(pid, SIGKILL);
}
void	test_built(t_token *token, t_minishell *mini)
{
	int		i;
	int		j;
	t_cmd	*aux;

	aux = mini->cmd;
	i = 0;
	j = 0;
	// resolver o export se caso a variável já existir, atualizar o valor
	// resolver o env (se a variável não tiver valor não pode ser imprimida no comando env mas tem que ser imprimida no export)
	// resolver o cd
	
	while (mini->cmd != NULL)
	{
		// while(aux->next)
		// {
		// 	if(aux->type == HEREDOC)
		// 		hand_heredoc(aux);
		// 	aux = aux->next;
		// }
		if (mini->cmd->type == WORD)
		{
			if (is_builtin(mini->cmd->name) == PWD)
				ft_pwd();
			else if (is_builtin(mini->cmd->name) == ECHO)
				ft_echo(mini->cmd);
			else if (is_builtin(mini->cmd->name) == CD)
				hand_cd(mini->cmd);
			else if (is_builtin(mini->cmd->name) == ENV)
				env(mini->cmd, &mini->table);
			else if (is_builtin(mini->cmd->name) == EXPORT)
				export(mini->cmd, mini->table);
			else if(is_builtin(mini->cmd->name) == UNSET)
				unset(mini, mini->cmd);
			else
				execution(mini->cmd, mini);
		}
		mini->cmd = mini->cmd->next;
	}
}
