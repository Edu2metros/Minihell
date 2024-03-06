/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/06 12:57:52 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\e[1;34m😤 Minishell\e[0m\e[1;33m -> \e[0m"
# define HEREDOC_PROMPT "\e[1;34m💡 HereDoc\e[0m\e[1;33m -> \e[0m"
# define TABLE_SIZE 500

# include "./libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

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
	FLAG,
	EXIST,
	READABLE,
	WRITEABLE,
	EXECUTABLE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

typedef struct s_export
{
	char			*key;
	char			*value;
	struct s_export	*next;
}					t_export;

typedef struct s_token
{
	int						type;
	int						space;
	char					*content;
	char					*aux;
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
	int						fd;
	char					*name;
	char					**args;
	struct s_cmd			*previous;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_hash_item
{
	char					*key;
	char					*value;
	struct s_hash_item		*next;
}							t_hash_item;

typedef struct s_hash_table
{
	struct s_hash_item		**item;
	int						size;
	int						count;
}							t_hash_table;

// t_minishell					*get_control(void);

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
	t_hash_table			*table;
}							t_minishell;

// Token functions
int							process_token_arg(char *input, t_minishell *mini,
								int i);
int							process_token_word(char *input, t_minishell *mini,
								int i, int start);
int							process_token_flag(char *input, t_minishell *mini,
								int i, int start);
int							process_token_dollar(char *input, t_minishell *mini,
								int i, int start);
int							process_token_builtin(char *input,
								t_minishell *mini, int i, int start);
int							process_token_operator(char *input,
								t_minishell *mini, int i, int start);
void						tokenizer(char *input, t_minishell *mini);
void						add_token(char *str, int type, int space,
								t_minishell *mini);

// Redirect functions
t_redirect_in				*new_redirect_in(char *content, int type);
t_redirect_in				*add_redirect_in(t_redirect_in *redirect,
								char *content, int type);
t_redirect_out				*add_redirect_out(t_redirect_out *redirect,
								char *content, int type);
t_redirect_out				*lstlast(t_redirect_out *lst);
t_redirect_out				*new_redirect_out(char *content, int type);
int							check_files(char *file_name);
void						hand_heredoc(t_cmd *cmd);
void						handle_redirects(t_minishell *mini);
void						handle_in_files(t_redirect_out *redirect);
void						handle_out_files(t_redirect_out *redirect);
void						redirect_in_list(t_token **token,
								t_redirect_in *redirect);
void						redirect_out_list(t_token **token,
								t_redirect_out *redirect);

// Print functions
void						print_cmd_args(t_cmd *cmd);
void						print_tokens(t_minishell *mini);
void						print_tokens(t_minishell *mini);
void						print_cmd_list(t_minishell *mini);

// CMD functions
t_cmd						*lst_first(t_cmd *cmd);
t_cmd						*cmd_new_node(char *content, int type);
t_cmd						*add_new_node(t_cmd *cmd, char *content, int type);
int							lstsize_pipe(t_token *token);
int							is_redirect(t_minishell *mini);
void						create_cmd_list(t_minishell *mini);
t_token						*populate_cmd_args(t_token *token, t_cmd *cmd);

// Builtins functions
void						ft_pwd(void);
void						hand_cd(t_cmd *cmd);
void						ft_echo(t_cmd *cmd);
void						env(t_cmd *cmd, t_hash_table **table);
void						test_built(t_token *token, t_minishell *mini);

// Error functions
void						handle_error(int nbr);

// Free functions
void						free_cmd(t_cmd **cmd);
void						lstclear_cmd(t_cmd **lst);
void						free_tokens(t_token **token);
void						free_redirect_in(t_redirect_in **redirect);
void						free_redirect_out(t_redirect_out **redirect);

// Utils functions
int							is_quote(char c);
int							is_builtin(char *input);
int							handle_pipe(char *prompt);
int							is_word(const char *input);
int							is_flag(const char *input);
int							ft_isalpha_mini(char input);
int							ft_redirect(char *prompt, int i);
int							handle_red(char *prompt, char c);
int							is_operator(char chr1, char chr2);
bool						validator(char *prompt);

// hash_table functions

t_hash_item					*create_item(char *key, char *value);
t_hash_table				*create_hash_table(int size);
t_hash_table				*hash_population(t_minishell *mini,
								t_hash_table **table);
unsigned long				hash_function(char *key);
void						free_item(t_hash_item *item);
void						free_table(t_hash_table **table);
void						erase_node(t_hash_table **table, t_hash_item *item,
								char *key);
void						erase_table(t_hash_table **table, char *key);
void						hand_hash_collision(t_hash_table **table,
								t_hash_item *item, int index);
void						hash_insert(t_hash_table **table, char *key,
								char *value);
char						*hash_search(t_hash_table *table, char *key);
void						print_table(t_hash_table **table);
int							ft_strcmp_len(char *s1, char *s2);

#endif