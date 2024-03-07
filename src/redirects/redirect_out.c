/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:35:41 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/07 18:41:05 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_out	*new_redirect_out(char *content, int type)
{
	t_redirect_out	*redirect;

	redirect = malloc(sizeof(t_redirect_out));
	if (!redirect)
		return (NULL);
	redirect->type = type;
	redirect->content = ft_strdup(content);
	redirect->fd_out = -1;
	redirect->next = NULL;
	return (redirect);
}

int	check_out_files(char *str)
{
	if (file_exist(str))
	{
		if (!file_is_writable(str))
		{
			printf("minishell: %s: Permission denied\n", str);
			exit (EXIT_FAILURE);
		}
	}
	if(file_is_executable(str))
	{
		printf("minishell: %s: Is a directory\n", str);
		exit (EXIT_FAILURE);
	}
	return (1);
}

void	redirect_out_list(t_token **token, t_redirect_out **redirect)
{
	t_redirect_out	*new_red;
	
	check_out_files((*token)->next->content);
	if ((*token))
	{
		new_red = new_redirect_out((*token)->next->content, (*token)->type);
		if (new_red != NULL)
		{
			if (*redirect == NULL)
				*redirect = new_red;
			else
				lstlast_out(*redirect)->next = new_red;
			handle_out_files(new_red);
		}
		*token = (*token)->next;
	}
}
