/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/02/28 14:24:38 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\e[1;34m😤 Minishell\e[0m\e[1;33m -> \e[0m"

// TOKEN
enum						e_token
{
	OUTPUT = 1,
	INPUT,
	PIPE,
	APPEND,
	HEREDOC,
	WORD,
	DOLLAR,
	QUOTE,
	DOUBLE_QUOTE,
	// IDENTIFIER
	FLAG,
	EXIST,
	READABLE,
	WRITEABLE,
	EXECUTABLE,
	// BUILT IN
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

# include "./libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_token
{
	int						type;
	char					*content;
	struct s_token			*next;
	struct s_token			*previous;
}							t_token;

typedef struct s_redirect_out
{
	int						type;
	char					*content;
	int						fd;
	struct s_redirect_out	*next;
}							t_redirect_out;

typedef struct s_redirect_in
{
	int						type;
	char					*content;
	int						fd;
	struct s_redirect_in	*next;
}							t_redirect_in;

typedef struct s_cmd
{
	int						type;
	int						count;

	char					*name;
	char					**args;
	struct s_cmd			*previous;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_minishell
{
	char					**path;
	char					*execute_path;
	char					**words;
	struct s_validation		*validations;
	t_cmd					*cmd;
	t_token					*token;
	t_redirect_in			*redirect_list_in;
	t_redirect_out			*redirect_list_out;
}							t_minishell;

t_minishell					*get_control(void);

void						handle_error(int nbr);
void						tokenizer(char *str, t_minishell *mini);
bool						validator(char *prompt);
int							check_quote(char *input);
int							meta_char(char c);
int							ft_redirect(char *prompt, int i);

// Utility Functions for Tokenization
void						add_token(char *str, int type, t_minishell *mini);
int							is_quote(char c);
int							is_operator(char chr1, char chr2);
int							is_word(const char *input);
int							is_flag(const char *input);
int							is_builtin(char *input);
int							token_list_size(t_token *token);
int							process_token_arg(char *input, t_minishell *mini,
								int i);
int							process_token_builtin(char *input,
								t_minishell *mini, int i, int start);
int							process_token_word(char *input, t_minishell *mini,
								int i, int start);
int							process_token_flag(char *input, t_minishell *mini,
								int i, int start);
int							process_token_operator(char *input,
								t_minishell *mini, int i, int start);
int							process_token_dollar(char *input, t_minishell *mini,
								int i, int start);
int							is_redirect(t_minishell *mini);
// int						redirect_or_pipe(t_minishell *mini);
void						ft_echo(t_minishell *mini, t_cmd *cmd);
void						ft_pwd(t_minishell *mini);
void						test_built(t_token *token, t_minishell *mini);
void						create_cmd_list(t_minishell *mini);
void						add_cmd(t_minishell *mini, t_token **token,
								t_cmd **cmd, int *count);
t_cmd						*cmd_new_node(char *content, int type);
void						populate_cmd_args(t_minishell *mini,
								t_token **token, t_cmd *cmd);
void						print_cmd_args(t_cmd *cmd);
void						hand_heredoc(t_minishell *mini);
void						print_tokens(t_minishell *mini);
void						ft_redirect_out(t_minishell *mini);
t_cmd						*lst_first(t_cmd *cmd);
void						lstclear_token(t_token **lst);
int							lstsize(t_token *lst);

#endif