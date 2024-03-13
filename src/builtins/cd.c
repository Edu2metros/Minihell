/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:33:44 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/12 21:05:13 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_how_many_char(char *str, char c)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			result++;
		i++;
	}
	return (result);
}

// lidar com relative path ou absolute path
// lidar com ..
// lidar com .
// lidar com cd sozinho

void	cd_absolute_path(char *absolute_path)
{
	if (chdir(absolute_path) == -1)
		ft_putendl_fd("cd: No such file or directory", 2);
	else
	{
		hash_insert(&get_control()->table, "OLDPWD",
			hash_search(get_control()->table, "PWD"));
		hash_insert(&get_control()->table, "PWD", absolute_path);
	}
}

void	ft_old_pwd(char *old)
{
	int		bar;
	int		i;
	char	*substr;

	bar = ft_how_many_char(old, '/');
	i = 0;
	while (old[i] != '\0' && bar > 1)
	{
		if (old[i] == '/')
			bar--;
		i++;
	}
	substr = ft_substr(old, 0, i - 1);
	if (chdir(substr) == -1)
		ft_putendl_fd("cd: No such file or directory", 2);
	else
	{
		hash_insert(&get_control()->table, "OLDPWD",
			hash_search(get_control()->table, "PWD"));
		hash_insert(&get_control()->table, "PWD", substr);
	}
}

void	relative_path(char *relative)
{
	char	*current;

	current = hash_search(get_control()->table, "PWD");
	current = ft_strjoin(current, "/");
	current = ft_strjoin(current, relative);
	if (chdir(current) == -1)
		ft_printf_fd(STDERR_FILENO, "cd: %s: No such file or directory\n", relative);
	else
	{
		hash_insert(&get_control()->table, "OLDPWD",
			hash_search(get_control()->table, "PWD"));
		hash_insert(&get_control()->table, "PWD", current);
	}
}

void	hand_cd(t_cmd *cmd)
{
	char	*current_directory;
	int		i;

	current_directory = hash_search(get_control()->table, "PWD");
	i = 1;
	if (cmd->args[i][0] == '/')
		cd_absolute_path(cmd->args[i]);
	else
	{
		if (ft_strlen(cmd->args[i]) == 2 && cmd->args[i][0] == '.'
			&& cmd->args[i][1])
			ft_old_pwd(cmd->args[i]);
		else if (ft_strlen(cmd->args[i]) == 1 && cmd->args[i][0] == '.')
			return ;
		else
			relative_path(cmd->args[i]);
	}
}
