/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/14 00:24:52 by  jaqribei        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\e[1;34m😤 Minishell\e[0m\e[1;33m -> \e[0m"

// META CHAR
// enum  e_token
// {
// 	OUTPUT = 1,
// 	INPUT,
// 	PIPE,
// 	QUOTE,
// 	D_QUOTE,
// 	APPEND
// 	HEREDOC,
// 	DOLLAR,
// 	WORD,
	// AND,
	// OR,
	// EXEC,
// };
# define OUTPUT 1
# define INPUT 2
# define PIPE 3
# define QUOTE 4
# define DOUBLE_QUOTE 5
# define APPEND 6
# define HEREDOC 7
# define DOLLAR 11

// IDENTIFIER
# define COMMAND 8
# define TOKEN 9
# define WORD -1
# define FLAG -2

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
	struct s_cmd		*cmd;
}						t_minishell;

typedef struct s_token
{
	int					type;
	char				*content;
	struct s_token		*next;
	struct s_token		*previous;
}						t_token;

typedef struct s_cmd
{
	int					type;
	char				*name;
	char				**args;
	struct s_cmd		*left;
	struct s_cmd		*right;
}						t_cmd;

void					handle_error(int nbr);
void					tokenizer(char *str, t_minishell *mini);
bool					validator(char *prompt);
int						check_quote(char *input);
int						meta_char(char c);
int						ft_redirect(char *prompt, int i);

// Utility Functions for Tokenization
void					add_token(char *str, int type, t_minishell *mini);
int						is_quote(char c);
int						is_operator(char chr1, char chr2);
int						is_word(const char *input);
int						is_flag(const char *input);
int						is_builtin(char *input);
int						process_token_arg(char *input, t_minishell *mini,
							int i);
int						process_token_builtin(char *input, t_minishell *mini,
							int i, int start);
int						process_token_word(char *input, t_minishell *mini,
							int i, int start);
int						process_token_flag(char *input, t_minishell *mini, int i,
							int start);
int						process_token_operator(char *input, t_minishell *mini,
							int i, int start);
int						process_token_dollar(char *input, t_minishell *mini,
							int i, int start);

#endif
