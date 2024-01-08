/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:55:41 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/08 19:05:43 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
>
<
>>
<<
|
'
"
*/

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
	if (!ft_strncmp(token, ">>", 2))
		return (DOUBLE_GREAT);
	if (!ft_strncmp(token, "<<", 2))
		return (DOUBLE_LESS);
	if (*token == '>')
		return (GREAT);
	if (*token == '<')
		return (LESS);
	if (*token == '|')
		return (PIPE);
	if (*token == '\'')
		return (QUOTE);
	if (*token == '"')
		return (DOUBLE_QUOTE);
	return(0);
}

void tokenizer(char **token)
{
	int key = 0;
	while(*token)
	{
		if(!ft_isalldigit(*token))
		{
			printf("%s\n", *token);
			key = check_tokenizer(*token);
			printf("%d\n", key);
		}
		else
		{
			printf("NÃO É\n");
		}
		token++;
	}
}

int main(void)
{
	const char *str;
	char **token;
	int key;

	str = NULL;
	while(1)
	{
		printf("Minishell $> ");
		str = readline(str);
		token = ft_split(str, ' ');
		tokenizer(token);
	}
}