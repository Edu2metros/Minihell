/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:33:44 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/29 14:31:36 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Sure, here is a step-by-step pseudocode to mimic the behavior of the cd (change directory) command in a shell:

Check if the command has arguments.

If no arguments are provided, change the directory to the home directory. This is usually represented by the environment variable HOME.
If there is one argument, proceed to the next step.
If there are more than one arguments, print an error message indicating too many arguments and return.
Check if the argument is a valid directory.

If the argument is not a valid directory, print an error message indicating the directory does not exist and return.
Change the current working directory to the directory specified in the argument.

Update the PWD (Present Working Directory) environment variable to reflect the new directory.

If there was an error in changing the directory, print an error message and return.

Return successfully.

Next, you could implement this pseudocode in your preferred programming language. Remember to handle errors and edge cases appropriately. */

void	hand_cd(t_cmd *cmd)
{
	char	*pwd;
	char 	*path;
	int		i;
	
	pwd = getcwd(NULL, 0);
	i = 1;
	
	if (!cmd->args[i])
		path = getenv("HOME");
	else
		path = cmd->args[i];
	if (chdir(path) != 0)
		handle_error(0); //path not find
	else
	{
		if (pwd != NULL)
			setenv("PWD", pwd, 1); // code my own setenv
		else 
			handle_error(0); //path not find
	}
}


