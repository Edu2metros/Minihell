/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/19 15:50:11 by jaqribei         ###   ########.fr       */
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
# define COMMAND 8
# define TOKEN 9
# define WORD -1
# define ARG -2

# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_minishell
{
	char				**path;
	char				*execute_path;
	char				**words;
	struct s_token		*token;
	struct s_validation	*validations;
}						t_minishell;

typedef struct s_token
{
	char				*content;
	int					type;
	char				**args;
	struct s_token		*next;
	struct s_token		*previous;
}						t_token;

int						check_quote(char *input);
void					handle_error(int nbr);
int						meta_char(char c);
int						ft_redirect(char *prompt, int i);
void					validator(char *prompt);

#endif
