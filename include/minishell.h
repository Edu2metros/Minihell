/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/10 13:29:50 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define GREAT 1
# define LESS 2
# define PIPE 3
# define QUOTE 4
# define DOUBLE_QUOTE 5
# define DOUBLE_GREAT 6
# define DOUBLE_LESS 7

# include "./libft/libft.h"
#include <unistd.h>
#include <unistd.h>
#include <readline/readline.h>

typedef struct s_minishell
{
	char	**path;
	char	*execute_path;
}			t_minishell;

int			ft_isalldigit_minishell(const char *str);
int validate_tokens(char **token, char **env, t_minishell *mini)
int	commands(char *token, char **env, t_minishell *mini)
char	*validate_cmd(t_minishell *mini, char *token)
void	get_path(char **env, t_minishell *mini)
int	check_tokenizer(char *token)

#endif
