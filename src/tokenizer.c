/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:55:41 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/09 11:46:44 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GREAT 1
#define LESS 2
#define PIPE 3
#define QUOTE 4
#define DOUBLE_QUOTE 5
#define DOUBLE_GREAT 6
#define DOUBLE_LESS 7

#include "../include/minishell.h"
#include <readline/readline.h>

int	check_tokenizer(char *token)
{
	if(ft_strlen(token) > 2)
		return(0);
	if (!ft_strncmp(token, ">>", 2))
		return (DOUBLE_GREAT);
	if (!ft_strncmp(token, "<<", 2))
		return (DOUBLE_LESS);
	if (!ft_strncmp(token, ">", 1))
		return (GREAT);
	if (!ft_strncmp(token, "<", 1))
		return (LESS);
	if (!ft_strncmp(token, "|", 1))
		return (PIPE);
	if (!ft_strncmp(token, "'", 1))
		return (QUOTE);
	if (!ft_strncmp(token, "\"", 1))
		return (DOUBLE_QUOTE);
	else
		return(0);
}


int	tokenizer(char **token)
{
	while (*token)
	{
		if (!ft_isalldigit_minishell(*token))
		{
			if(check_tokenizer(*token) == 0)
				return(0);
		}
		else
		{
			printf("NÃO É\n");
		}
		token++;
	}
	return(1);
}

int	main(void)
{
	const char *str;
	char **token;
	int key;
	key = 0;
	str = NULL;
	while (1)
	{
		printf("Minishell $> ");
		str = readline(str);
		token = ft_split(str, ' ');
		key = tokenizer(token);
		if(key == 0)
		{
			free(token);
			printf("erro\n");
			// return(0);
		}
	}
}
