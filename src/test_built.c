/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:48:30 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/16 14:50:19 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void test_built(t_token *token, t_minishell *mini)
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
				ft_pwd(mini);
		}
		token = token->next;
	}
}