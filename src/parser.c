/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/16 15:21:17 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Set up Table of commands

//reads token list 
//breaks a pipeline into commands
//A pipeline is a list of commands separated by |
//A command comprises both the command name/path, its flags and associates redirections.

void	set_table_command(t_minishell *mini)
{
	t_token	*token;
	
	token = mini->token;
	while (token != NULL)
	{
		while(token->content != PIPE)
		{
			//array of commands receive all previous token
		}
	}
	
}