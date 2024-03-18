/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:02:27 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/18 11:20:01 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*lst_first(t_cmd *cmd)
{
	t_cmd	*result;

	result = cmd;
	while (result != NULL && result->previous != NULL)
 		result = result->previous;
	return (result);
}

int	is_redirect(t_token *token)
{
	int	type;

	type = token->type;
	if (type == OUTPUT || type == INPUT || type == APPEND || type == HEREDOC)
		return (type);
	return (0);
}

int	lstsize_pipe(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == PIPE)
			return (i);
		i++;
		token = token->next;
	}
	return (i);
}

void	shift_args(char **args, int start)
{
	int	j;

	j = start;
	while (args[j])
	{
		args[j] = args[j + 1];
		j++;
	}
	free(args[j]);
}

void	remove_redirect(t_cmd *cmd)
{
	t_cmd	*aux;
	int		i;

	aux = lst_first(cmd);
	while (aux)
	{
		i = 0;
		while (aux->args[i])
		{
			if (ft_strcmp(aux->args[i], ">") == 0 || ft_strcmp(aux->args[i],
					">>") == 0 || ft_strcmp(aux->args[i], "<") == 0)
			{
				free(aux->args[i]);
				shift_args(aux->args, i);
				if (aux->args[i])
				{
					free(aux->args[i]);
					shift_args(aux->args, i);
				}
				if (aux->args[i] && !ft_isredirect(aux->args[i]))
					aux->name = ft_strdup(aux->args[i]);
			}
			else if (ft_strcmp(aux->args[i], "<<") == 0)
			{
				free(aux->args[i]);
				shift_args(aux->args, i);
				if (aux->args[i])
				{
					free(aux->args[i]);
					unlink("heredoc");
					shift_args(aux->args, i);
				}
				if (aux->args[i] && !ft_isredirect(aux->args[i]))
					aux->name = ft_strdup(aux->args[i]);
			}
			else
				i++;
		}
		aux = aux->next;
	}
}
