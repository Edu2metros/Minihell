/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:20:03 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/20 17:49:15 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	free_remove_aux(t_cmd *aux, int i)
{
	if (ft_strcmp(aux->args[i], ">") == 0 || ft_strcmp(aux->args[i], ">>") == 0
		|| ft_strcmp(aux->args[i], "<") == 0)
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
		return (1);
	}
	else if (ft_strcmp(aux->args[i], "<<") == 0)
	{
		free(aux->args[i]);
		shift_args(aux->args, i);
		free_remove_aux2(aux, i);
		return (1);
	}
	return (0);
}

void	free_remove_aux2(t_cmd *aux, int i)
{
	if (aux->args[i])
	{
		free(aux->args[i]);
		unlink("heredoc");
		shift_args(aux->args, i);
	}
	if (aux->args[i] && !ft_isredirect(aux->args[i]))
		aux->name = ft_strdup(aux->args[i]);
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
			if (free_remove_aux(aux, i))
				continue ;
			else
				i++;
		}
		aux = aux->next;
	}
	check_errors(cmd);
}

void	check_errors(t_cmd *cmd)
{
	t_cmd	*aux;

	aux = lst_first(cmd);
	while (aux)
	{
		if (aux->name == NULL)
			aux->return_status = 1;
		aux = aux->next;
	}
}
