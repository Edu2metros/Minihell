/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:56 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/23 13:01:30 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hand_heredoc(t_minishell *mini)
{
	t_token	*token;
	char	*delimiter;
	char	*input;
	int		fd;
	
	token = mini->token;
	while (token)
	{
		if (token->type == HEREDOC && token->next->type == WORD)
		{
			delimiter = token->next->content;
			fd = open("Heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (1)
			{
				input = readline("> ");
				if (!input || !(ft_strcmp(input, delimiter)))
				{
					free(input);
					close(fd);
					unlink("Heredoc");
					break ;
				}
				ft_putendl_fd(input, fd);
				free(input);
			}
		}
		token = token->next;
	}
}


void	hand_redirect(t_minishell *mini)
{
	t_token	*token;
	char	*file;
	char	*input;
	int		fd;
	
	token = get_control()->token;
	while (token)
	{
		if (is_redirect(mini) && token->next != NULL)
		{
			if (token->type == INPUT)
				hand_input(); // validação - se existe e tem permição 
			if (token->type == OUTPUT)
				hand_output(); /// validação - se existe e tem permição 
			if (token->type == APPEND)
				hand_output(); // validação - se existe e tem permição 
			if (token->type == HEREDOC)
				heredoc(mini);
		}
	}
	token = token->next;
}

void	hand_input(t_minishell *mini)
{
	if (!validate_files());
		exit(EXIT_FAILURE);
	
	
}

int	validate_input_file(t_token *token)
{
	int	file_status;
	
	file_status = check_files(token->next->content);
	if (token->type == INPUT)
	{
		if (file_status != EXIST)
		{
			printf("no such file or directory\n");
			exit(EXIT_FAILURE);
		}
		else if (file_status != READABLE)
		{
			printf("permission denied\n");
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

int	check_files(char *file_name)
{
	if (access(file_name, F_OK) == -1)
		return (EXIST);
	if (access(file_name, R_OK) == -1)
		return (READABLE);
	if (access(file_name, W_OK) == -1)
		return (WRITEABLE);
	if (access(file_name, X_OK) == -1)
		return (EXECUTABLE);
}

// 			file = token->next->content;
// 			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			while (1)
// 			{
// 				input = readline("> ");
// 				if (!input || !(ft_strcmp(input, delimiter)))
// 				{
// 					free(input);
// 					close(fd);
// 					unlink("Heredoc");
// 					break ;
// 				}
// 				ft_putendl_fd(input, fd);
// 				free(input);
// 			}
// 		}
// 		token = token->next;
// 	}
// }
// token = mini->token;
// 	while (token)
// 	{
// 		if (token->type == OUTPUT && token->next->type == WORD)
// 		{
// 			//manda pra função que cuida disso
// 			//manda pra de validar
// 			// saida - existe e se tem permissã
// 			// entrada - existe e permissão 

// 			>> o_append
// 			> o_trunc