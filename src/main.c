/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:48:59 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/16 14:11:01 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_minishell	*get_control(void)
{
	static t_minishell	control;

	return (&control);
}

int	ft_isredirect(char *string)
{
	if (ft_strncmp(string, ">", 2) == 0 || ft_strncmp(string, ">>", 3) == 0
		|| ft_strncmp(string, "<", 2) == 0 || ft_strncmp(string, "<<", 3) == 0)
		return (1);
	return (0);
}

void	pipe_or_not(t_minishell *mini, t_cmd *cmd)
{
	if (cmd->next == NULL && cmd->name == NULL)
		return ;
	if (cmd->next == NULL)
		exec_command(cmd, mini);
	else
		exec_pipe(mini, cmd);
}

// hashtable:
//item
//env

//hash item:
//key
//value
//next

void free_hashs(t_hash_table *hash)
{
	int i;
	i = 0;
	while(i < hash->size) // free na tabela hash item
	{
		if (hash->item[i] != NULL)
		{
			free(hash->item[i]->key);
			if(hash->item[i]->value != NULL)
				free(hash->item[i]->value);
			free(hash->item[i]);
		}
		i++;
	}
	free_split(hash->env);
}

void free_out_while(t_minishell *mini)
{
	// free_hashs(mini->table);
	// hashtable
	// args env
	// free_while()
}

static void	minishell(t_minishell *mini, t_hash_table *table)
{
	char	*input;

	while (TRUE)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		get_control()->heredoc = 0;
		input = readline(PROMPT);
		handle_control_d(input, table);
		add_history(input);
		if (!validator(input))
			continue ;
		tokenizer(input, mini);
		create_cmd_list(mini);
		get_heredoc();
		if (get_control()->heredoc)
			return ;
		pipe_or_not(mini, lst_first(mini->cmd));
		close_fd(mini);
		free_all(mini);
	}
	clear_history();
	free_out_while(mini);
}

int	main(void)
{
	t_minishell	*mini;
	ft_bzero(get_control(), sizeof(t_minishell));
	mini = get_control();
	mini->table = hash_population(mini, &mini->table);
	minishell(mini, mini->table);
}
