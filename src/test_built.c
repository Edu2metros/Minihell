/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:48:30 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/26 12:20:19 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_minishell *mini)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if(pwd)
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("error", 1);
	mini->pwd = ft_calloc((ft_strlen(pwd) + 1), sizeof(char *));
	if(mini->pwd)
		mini->pwd = ft_strdup(pwd);
	free(pwd);
}

void	ft_echo(t_minishell *mini)
{
	int		n_flag;
	int		i;
	// char	**args;

	// args = mini->cmd->args;
	n_flag = 0;
	i = 0;
	if (!get_control()->cmd->args)
		ft_putstr_fd("\n", 1);
	else
	{
		while (get_control()->cmd->args[i] && ft_strncmp(get_control()->cmd->args[i], "-n", 2) == 0)
		{
			n_flag = 1;
			i++;
		}
		while (get_control()->cmd->args[i] != NULL)
		{
			ft_putstr_fd(get_control()->cmd->args[i], 1);
			if (get_control()->cmd->args[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if(n_flag == 0)
		ft_putstr_fd("\n", 1);
}

/* void test_built(t_token *token, t_minishell *mini)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (token != NULL)
	{
		if (token->type == WORD && is_builtin(token->content) < 0)
		{
			if (is_builtin(token->content) == PWD)
			{	
				printf("\n=========================    PWD    =========================\n\n");
				ft_pwd(mini);
			}
			// if (is_builtin(token->content) == ECHO)
			// 	ft_echo(mini);
		}
		if (token->type == HEREDOC)
		{
			printf("\n=========================  HEREDOC  =========================\n\n");
			ft_heredoc(mini);
		}
		// if (token->type == OUTPUT)
		// {
		// 	printf("\n=========================  OUTPUT  =========================\n\n");
		// 	ft_redirect_out(mini);
		// }
		token = token->next;
	}
} */