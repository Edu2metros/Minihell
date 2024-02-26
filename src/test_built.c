/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:48:30 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/26 17:31:37 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_minishell *mini)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("error", 1);
	mini->pwd = ft_calloc((ft_strlen(pwd) + 1), sizeof(char *));
	if (mini->pwd)
		mini->pwd = ft_strdup(pwd);
	free(pwd);
}

void	test_built(t_token *token, t_minishell *mini)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini->cmd != NULL)
	{
		if (mini->cmd->type == WORD && is_builtin(mini->cmd->name) < 0)
		{
			if (is_builtin(token->content) == PWD)
			{
				printf("\n=========================    PWD    =========================\n\n");
				ft_pwd(mini);
			}

			if (is_builtin(mini->cmd->name) == ECHO)
			{
				printf("\n=========================    ECHO    =========================\n\n");
				ft_echo(mini, mini->cmd);
			}
		}
		if (token->type == HEREDOC)
		{
			printf("\n=========================  HEREDOC  =========================\n\n");
			hand_heredoc(mini);
		}
		// if (token->type == OUTPUT)
		// {
		// 	printf("\n=========================  OUTPUT  =========================\n\n");
		// 	ft_redirect_out(mini);
		// }
	mini->cmd = mini->cmd->next;
	}
}