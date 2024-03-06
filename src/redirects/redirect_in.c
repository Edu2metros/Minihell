/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:33:51 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/06 20:11:05 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_in	*new_redirect_in(char *content, int type)
{
	t_redirect_in	*redirect;

	redirect = malloc(sizeof(t_redirect_in));
	if (!redirect)
		return (NULL);
	redirect->type = type;
	redirect->content = ft_strdup(content);
	redirect->fd_in = -1;
	redirect->next = NULL;
	return (redirect);
}

void	redirect_in_list(t_token **token, t_redirect_in **redirect)
{
	t_redirect_in	*new_red_in;

	if ((*token)->type == INPUT)
	{
		if (file_exist((*token)->next->content))
		{	
			printf("minishell: %s: No such file or directory\n",
				(*token)->next->content);
			EXIT_FAILURE;
		}
		else if (!file_is_readable((*token)->next->content))
		{
			printf("minishell: %s: Permission denied\n",
				(*token)->next->content);
			EXIT_FAILURE;
		}
	}
	new_red_in = new_redirect_in((*token)->next->content, (*token)->type);
	if (new_red_in != NULL)
	{
		if (*redirect == NULL)
			*redirect = new_red_in;
		else
			lstlast_in(*redirect)->next = new_red_in;
		handle_in_files(new_red_in);
	}
	*token = (*token)->next;
}