/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/29 19:07:15 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// META CHAR

# define GREAT 10
# define LESS 2
# define PIPE 3
# define QUOTE 4
# define DOUBLE_QUOTE 5
# define DOUBLE_GREAT 6
# define DOUBLE_LESS 7
# define DOLLAR 11

// IDENTIFIER
# define COMMAND 8
# define TOKEN 9
# define WORD -1
# define ARG -2

// BUILT IN
# define ECHO -3
# define CD -4
# define PWD -5
# define EXPORT -6
# define UNSET -7
# define ENV -8
# define EXIT -9

# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
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
	int					type;
	char				*content;
	char				**args;
	struct s_token		*next;
	struct s_token		*previous;
}						t_token;

int						check_quote(char *input);
void					handle_error(int nbr);
int						meta_char(char c);
int						ft_redirect(char *prompt, int i);
bool					validator(char *prompt);
void					tokenizer(char *str, t_minishell *mini);

// Utility Functions for Tokenization
int						is_quote(char c);
int						is_operator(char chr1, char chr2);
int						is_word(const char *input);
int						is_arg(const char *input);
int						is_builtin(char *input);
void					add_token(char *str, int type, t_minishell *mini);
int						process_token_quote(char *input, t_minishell *mini,
							int i);
int						process_token_builtin(char *input, t_minishell *mini,
							int i, int start);
int						process_token_word(char *input, t_minishell *mini,
							int i, int start);
int						process_token_arg(char *input, t_minishell *mini, int i,
							int start);
int						process_token_operator(char *input, t_minishell *mini,
							int i, int start);
int						process_token_dollar(char *input, t_minishell *mini,
							int i, int start);

#endif
