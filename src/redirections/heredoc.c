/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:08:56 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/27 19:10:40 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line ("", 0);
		rl_redisplay();
		// exit(130);
	}
}

void	hand_heredoc(t_minishell *mini)
{
	t_token	*token;
	char	*delimiter;
	char	*input;
	int		fd;
	
	pid_t pid = fork();
	if(signal(SIGINT, signal_handler))
	{
		printf("saiu\n");
		return ;
	}
	token = mini->token;
	while (token && !pid)
	{
		if (token->type == HEREDOC && token->next->type == WORD)
		{
			delimiter = token->next->content;
			fd = open("Heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			while (1)
			{
				input = readline(">>>>> ");
				if (!input || (ft_strcmp(input, delimiter) == 0))
				{
					free(input);
					close(fd);
					unlink("Heredoc");
					break;
				}
				ft_putendl_fd(input, fd);
				free(input);
			}
		}
		token = token->next;
	}
	if(pid == 0)
		exit(1);
	waitpid(pid, NULL, NULL);
}


/* void	hand_redirect(t_minishell *mini)
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
} */

/* void	hand_input(t_minishell *mini)
{
	if (!validate_files());
		exit(EXIT_FAILURE);
	
	
} */

/* int	validate_input_file(t_token *token)
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
} */

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