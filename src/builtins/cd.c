/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:33:44 by jaqribei          #+#    #+#             */
/*   Updated: 2024/03/19 12:26:00 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd_insert(char *absolute_path)
{
	hash_insert(&get_control()->table, "OLDPWD", \
	hash_search(get_control()->table, "PWD"));
	hash_insert(&get_control()->table, "PWD", absolute_path);
	get_control()->return_status = 0;
}

void	cd_absolute_path(char *absolute_path)
{
	if (absolute_path == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: HOME not set\n");
		get_control()->return_status = 1;
		return ;
	}
	if (access(absolute_path, F_OK) == 0 && (access(absolute_path, X_OK) == -1))
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: Permission denied\n", \
		absolute_path);
		get_control()->return_status = 1;
		return ;
	}
	if (chdir(absolute_path) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: No such file or directory\n", \
		absolute_path);
		get_control()->return_status = 1;
	}
	else
		cd_insert(absolute_path);
}

void	ft_old_pwd(char *old)
{
	int		bar;
	int		i;
	char	*substr;
	char	*tmp;

	bar = ft_how_many_char(old, '/') + 1;
	tmp = hash_search(get_control()->table, "PWD");
	i = ft_strlen(tmp);
	if (tmp[i - 1] == '/')
		i = i - 2;
	while (bar > 0)
	{
		if (tmp[i] == '/')
			bar--;
		i--;
	}
	substr = ft_substr(tmp, 0, i + 1);
	if (chdir(substr) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: No such file or directory\n", old);
		get_control()->return_status = 1;
	}
	else
		cd_insert(substr);
}

void	relative_path(char *relative)
{
	char	*current;

	current = hash_search(get_control()->table, "PWD");
	if (current[ft_strlen(current) - 1] != '/')
		current = ft_strjoin(current, "/");
	current = ft_strjoin(current, relative);
	if (access(current, F_OK) == 0 && (access(current, X_OK) == -1
			|| access(current, R_OK) == -1))
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: Permission denied\n", relative);
		get_control()->return_status = 1;
		return ;
	}
	if (chdir(current) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: No such file or directory\n", \
		relative);
		get_control()->return_status = 1;
	}
	else
		cd_insert(current);
}

void	hand_cd(t_cmd *cmd)
{
	char	*current_directory;
	int		i;

	current_directory = hash_search(get_control()->table, "PWD");
	i = 1;
	if (cmd->args[i] == NULL)
		cd_absolute_path(hash_search(get_control()->table, "HOME"));
	else if (current_directory == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: PWD not set\n");
		get_control()->return_status = 1;
	}
	else if (cmd->args[i][0] == '/')
		cd_absolute_path(cmd->args[i]);
	else if (ft_strlen(cmd->args[i]) == 2 && cmd->args[i][0] == '.'
		&& cmd->args[i][1])
		ft_old_pwd(cmd->args[i]);
	else if (ft_strlen(cmd->args[i]) == 1 && cmd->args[i][0] == '.')
		get_control()->return_status = 0;
	else
		relative_path(cmd->args[i]);
	if (get_control()->cmd->on_fork == 1)
		exit(get_control()->return_status);
}
