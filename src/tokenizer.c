/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:55:41 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/10 13:30:16 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	get_path(char **env, t_minishell *mini)
{
	while (ft_strncmp(*env, "PATH=", 5))
		env++;
	*env += 5;
	mini->path = ft_split(*env, ':');
}

char	*validate_cmd(t_minishell *mini, char *token)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	while (mini->path[i] != NULL)
	{
		tmp = ft_strjoin(mini->path[i], "/");
		result = ft_strjoin(tmp, token);
		free(tmp);
		if (access(result, X_OK) == 0)
			return (result);
		free(result);
		i++;
	}
	return (NULL);
}

#include <sys/wait.h>

int	commands(char *token, char **env, t_minishell *mini)
{
	int		i;
	int		pid;
	char	*args[3];

	i = 0;
	mini->execute_path = validate_cmd(mini, token);
	if (mini->execute_path == NULL)
		perror("Command not found");
	else
	{
		pid = fork();
		if (pid == 0)
		{
			args[0] = mini->execute_path;
            args[1] = token;
            args[2] = NULL;
			execve(mini->execute_path, args, env);
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, NULL, 0);
	}
	free(mini->execute_path);
	return (0);
}

int validate_tokens(char **token, char **env, t_minishell *mini)
{
	while (*token)
	{
		if (!ft_isalldigit_minishell(*token))
		{
			if (check_tokenizer(*token) == 0)
				return (0);
		}
		else
			commands(*token, env, mini);
		token++;
	}
	return (1);
}

