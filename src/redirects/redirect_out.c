/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:35:41 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/06 20:11:56 by eddos-sa         ###   ########.fr       */
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

void	redirect_out_list(t_token **token, t_redirect_out **redirect)
{
	t_redirect_out	*new_red;

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
	*token = first(token);

	// if ((*token)->type == OUTPUT || (*token)->type == APPEND)
	// {
	// 	if (check_files((*token)->next->content) == EXIST)
	// 	{
	// 		if (check_files((*token)->next->content) != WRITEABLE)
	// 		{
	// 			printf("minishell: %s: Permission denied\n",
	// 				(*token)->next->content);
	// 			clear_token_node(token, *token);
	// 			return ;
	// 		}
	// 		if (check_files((*token)->next->content) == EXECUTABLE)
	// 		{
	// 			printf("minishell: %s: Is a directory\n",
	// 				(*token)->next->content);
	// 			clear_token_node(token, *token);
	// 			return ;
	// 		}
	// 	}		
	// }
}
