
// void	get_path(char **env, t_minishell *mini)
// {
// 	while (ft_strncmp(*env, "PATH=", 5))
// 		env++;
// 	*env += 5;
// 	mini->path = ft_split(*env, ':');
// }

// char	*validate_cmd(t_minishell *mini, char *token)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*result;

// 	i = 0;
// 	while (mini->path[i] != NULL)
// 	{
// 		tmp = ft_strjoin(mini->path[i], "/");
// 		result = ft_strjoin(tmp, token);
// 		free(tmp);
// 		if (access(result, X_OK) == 0)
// 			return (result);
// 		free(result);
// 		i++;
// 	}
// 	return (NULL);
// }

// int	commands(char *token, char **env, t_minishell *mini)
// {
// 	mini->execute_path = validate_cmd(mini, token);
// 	if (mini->execute_path == NULL)
// 		return (0);
// 	else
// 		return (1);
// }

// void	print_error(char *token, int nbr)
// {
// 	if (nbr == COMMAND)
// 		printf("%s: Command not found.\n", token);
// 	if (nbr == TOKEN)
// 		printf("Token \'%s' not found.\n", token);
// }