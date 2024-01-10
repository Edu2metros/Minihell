/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:55:41 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/10 14:14:00 by eddos-sa         ###   ########.fr       */
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

int	commands(char *token, char **env, t_minishell *mini)
{
	mini->execute_path = validate_cmd(mini, token);
	if (mini->execute_path == NULL)
		printf("Command \"%s"
				"not found",
				token);
	else
		return (1);
	return (0);
}

void	print_error(char *token, int nbr)
{
	if (nbr == COMMAND)
		printf("Command \'%s' not found.", token);
	if (nbr == TOKEN)
		printf("Token \'%s' not found.", token);
}

int	validate_tokens(char **token, char **envp, t_minishell *mini)
{
	while (*token)
	{
		if (!ft_isalldigit_minishell(*token))
		{
			if (check_tokenizer(*token) == 0)
			{
				print_error(*token, TOKEN);
				return (0);
			}
		}
		else if (commands(*token, envp, mini) == 0)
		{
			print_error(*token, COMMAND);
			return (0);
		}
		token++;
	}
}
