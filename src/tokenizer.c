/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:55:41 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/09 14:48:38 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>

int	check_tokenizer(char *token)
{
	if (ft_strlen(token) > 2)
		return (0);
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
		return (0);
}

/*
achar o path
transformar em um array de strings
concatenar
pegar o comando e usar o acess em cada uma e ver se é executavel
*/

void	get_path(char **env)
{
	t_minishell	*mini;

	while (ft_strncmp(*env, "PATH=", 5))
		env++;
	*env += 5;
	mini->path = ft_split(*env, ':');
}

int	commands(char *token, char **env)
{
	get_path(env);
}

int	validate_tokens(char **token, char **env)
{
	while (*token)
	{
		if (!ft_isalldigit_minishell(*token))
		{
			if (check_tokenizer(*token) == 0)
				return (0);
		}
		else
		{
			commands(*token, env);
		}
		token++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	const char	*str;
	char		**token;
	int			key;

	key = 0;
	str = NULL;
	while (1)
	{
		printf("Minishell $> ");
		str = readline(str);
		printf("%s\n", str);
		token = ft_split(str, ' ');
		key = validate_tokens(token, envp);
		if (key == 0)
			printf("Command not found.\n");
	}
}
