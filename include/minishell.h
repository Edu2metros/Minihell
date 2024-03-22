/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/22 20:14:06 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\e[1;34m😤 Minishell\e[0m\e[1;33m -> \e[0m"
# define HEREDOC_PROMPT "\e[1;34m💡 HereDoc\e[0m\e[1;33m -> \e[0m"

# define TABLE_SIZE 500
# define INT_MAX 2147483647
# define INT_MIN -2147483648

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
	EXIT,
	TRUE,
	FALSE,
	OTHER
};

typedef struct s_export
{
	char					*key;
	char					*value;
	struct s_export			*next;
}							t_export;

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
	int						fd_out;
	struct s_redirect_out	*next;
	struct s_redirect_out	*previous;
}							t_redirect_out;

typedef struct s_redirect_in
{
	int						type;
	char					*content;
	int						fd_in;
	int						heredoc;
	struct s_redirect_in	*next;
	struct s_redirect_in	*previous;
}							t_redirect_in;

typedef struct s_cmd
{
	int						type;
	int						count;
	int						space;
	int						fd[2];
	int						on_fork;
	int						return_status;
	char					*name;
	char					**args;
	struct s_cmd			*previous;
	struct s_cmd			*next;
	struct s_redirect_out	*redirect_list_out;
	struct s_redirect_in	*redirect_list_in;
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
	char					**env;
}							t_hash_table;

typedef struct s_pipe
{
	int						pipe_count;
	int						fd[2];
	int						backup_read;
	t_cmd					*cmd_output;
	t_cmd					*cmd_input;
	struct s_pipe			*next;
}							t_pipe;

typedef struct s_minishell
{
	int						flag;
	int						return_status;
	int						signals;
	char					**path;
	char					*execute_path;
	char					**words;
	int						heredoc;
	t_pipe					*pipe;
	t_cmd					*cmd;
	t_token					*token;
	t_redirect_in			*redirect_list_in;
	t_redirect_out			*redirect_list_out;
	t_hash_table			*table;
}							t_minishell;

t_minishell					*get_control(void);

// Execution functions
int							is_directory(const char *path);

char						*search_path(char **path, char *command);
char						*get_path(t_minishell *mini, char *command);

void						path_null(char *str);
void						exec_redirect(t_cmd *cmd);
void						pipe_or_not(t_minishell *mini);
void						execute_without_path(t_cmd *cmd);
void						exec_pipe(t_minishell *mini, t_cmd *cmd);
void						exec_command(t_cmd *cmd, t_minishell *mini);
void						exec_pipe_command(t_cmd *cmd, t_minishell *mini);
void						single_command_child(t_cmd *cmd, t_minishell *mini);
void						fork_processes(t_minishell *mini, t_cmd *cmd,
								int fd_in);
void						wait_processes(t_minishell *mini, t_cmd *aux,
								int count);
void						handle_parent_process(t_cmd **cmd, int fd[],
								int *fd_in);
void						handle_child_process(t_cmd *cmd, t_minishell *mini,
								int fd[], int fd_in);

// Built ins functions
int							is_builtin(char *input);
void						builtin_execution(t_cmd *cmd, t_minishell *mini);
// CD

void						hand_cd(t_cmd *cmd);
void						ft_old_pwd(char *old);
void						relative_path(char *relative);
void						cd_insert(char *absolute_path);
void						cd_absolute_path(char *absolute_path);

int							ft_strchr_flag(const char *s, int c);

// ECHO

void						ft_echo(t_cmd *cmd);
void						ft_echo_handler(t_cmd *cmd, int fd_out, int n_flag);

// ENV
void						env(t_cmd *cmd, t_hash_table **table);

// EXIT
void						ft_exit(t_cmd *node, t_hash_table **table);
int							validate_numeric_string(char *str,
								int *code_status);
void						free_exit(t_minishell *mini, t_hash_table **table,
								int status);
int							convert_and_check_range(char *str, int *code_status,
								long number);

// EXPORT
void						export(t_cmd *cmd, t_hash_table *hash);
void						hash_update_value(t_hash_table *hash, char *key);
void						extract_key_value(char *arg, char **key,
								char **value);
;

// UNSET
void						unset(t_minishell *mini, t_cmd *cmd);
void						hash_delete(t_hash_table *table, char *key);
void						delete_variable_env(t_hash_table *table, char *key);

// PWD
void						ft_pwd(t_cmd *cmd);

// Table functions
t_hash_table				*create_hash_table(int size);
t_hash_table				*hash_population(t_hash_table **table);

t_hash_item					*create_item(char *key, char *value);

unsigned long				hash_function(char *key);

char						*hash_search(t_hash_table *table, char *key);

void						hash_insert_equals(char **str);
void						populate_env(t_hash_table *table, int len);
void						hash_insert(t_hash_table **table, char *key,
								char *value);
void						hand_hash_collision(t_hash_table **table,
								t_hash_item *item, int index);

// Free functions
int							free_remove_aux(t_cmd *aux, int i);

void						free_cmd(t_cmd **cmd);
void						free_reds(t_cmd *aux);
void						free_array(char **array);
void						lstclear_cmd(t_cmd **lst);
void						free_split(char **splited);
void						remove_redirect(t_cmd *cmd);
void						free_tokens(t_token **token);
void						free_item(t_hash_item *item);
void						lstclear_token(t_token *lst);
void						free_token(t_minishell *mini);
void						free_node(t_redirect_in *red);
void						free_hashs(t_hash_table *hash);
void						free_args(t_cmd *current, int i);
void						free_all_child(t_minishell *mini);
void						free_all(t_minishell *minishell);
void						free_table(t_hash_table **table);
void						free_out_while(t_minishell *mini);
void						free_export(t_export *temp_export);
void						free_remove_aux2(t_cmd *aux, int i);
void						free_n_exit_child(t_minishell *mini);
void						free_token_dolar(char *tmp, char *substr);
void						free_redirect_in(t_redirect_in **redirect);
void						free_redirect_out(t_redirect_out **redirect);
void						erase_table(t_hash_table **table, char *key);
void						clear_heredoc_child_process(t_minishell *mini);
void						erase_node(t_hash_table **table, t_hash_item *item,
								char *key);

// Token functions
int							expand_variable(t_token *token, int i);
int							process_token_arg(char *input, t_minishell *mini,
								int i);
int							process_token_word(char *input, t_minishell *mini,
								int i, int start);
int							process_token_flag(char *input, t_minishell *mini,
								int i, int start);
int							process_token_quote(char *input, t_minishell *mini,
								int i, int start);
int							process_token_dollar(char *input, t_minishell *mini,
								int i, int start);
int							process_token_builtin(char *input,
								t_minishell *mini, int i, int start);
int							process_token_operator(char *input,
								t_minishell *mini, int i, int start);

char						*expand_variable_word(char *input,
								t_minishell *mini);
char						*expand_val(char *input, int *i, t_minishell *mini,
								char *result);

void						remove_quote(char *substr);
void						next_quote(t_token *token);
void						add_token_space(char *input, int i);
void						tokenizer(char *input, t_minishell *mini);
void						handle_quote_aux(t_token *token, int i, char type);
void						handle_single_quote(char *substr, char **new_str,
								int *i);
void						handle_double_quote(char *substr, char **new_str,
								int *i);
void						add_token(char *str, int type, int space,
								t_minishell *mini);

// Parser functions
void						create_cmd_list(t_minishell *mini);

t_token						*populate_cmd_args(t_token *token, t_cmd *cmd);

t_cmd						*cmd_new_node(char *content, int type, int space);
t_cmd						*add_new_node(t_cmd *cmd, char *content, int type,
								int space);

// Validator functions
int							handle_pipe(char *prompt);
int							handle_error_two(char *prompt);
int							handle_red(char *prompt, char c);
int							handle_quote_val(char *prompt, int *i);
int							handle_pipe_char(char *prompt, int *i);
int							handle_char_red(char *prompt, char c, int *i);

// Redirects functions
t_redirect_in				*lstlast_in(t_redirect_in *lst);
t_redirect_in				*lst_first_in(t_redirect_in *redirect);
t_redirect_in				*new_redirect_in(char *content, int type);

t_redirect_out				*lstlast_out(t_redirect_out *lst);
t_redirect_out				*lst_first_out(t_redirect_out *lst);
t_redirect_out				*new_redirect_out(char *content, int type);

int							check_in_files(char *str, t_cmd *cmd);
int							check_out_files(char *str, t_cmd *cmd);

void						wait_heredoc(pid_t pid);
void						handle_redirects(t_minishell *mini);
void						clear_list_in(t_redirect_in **redirect);
void						clear_list_out(t_redirect_out **redirect);
void						get_heredoc(t_cmd *cmd, t_redirect_in *red);
void						handle_in_files(t_redirect_in *redirect,
								t_cmd *cmd);
void						handle_out_files(t_redirect_out *redirect,
								t_cmd *cmd);
void						hand_heredoc(char *delimiter, int fd,
								t_redirect_in *red);
void						heredoc_child_process(char *delimiter, int fd,
								t_redirect_in *red);
void						set_heredoc(t_token **token,
								t_redirect_in **redirect, t_cmd *cmd);
void						redirect_in_list(t_token **token,
								t_redirect_in **redirect, t_cmd *cmd);
void						redirect_out_list(t_token **token,
								t_redirect_out **redirect, t_cmd *cmd);

// Signal functions
void						sig_ignore(void);
void						hand_signals(void);
void						setup_signals(void);
void						handle_sigint(int sig);
void						handle_sigint_child(int sig);
void						handle_sigquit_signal(int sig);
void						handle_sigint_heredoc(int sig);
void						handle_control_d(char *input, t_hash_table *table);

// Utils functions
t_export					*create_new_export(t_hash_item *current_item);
t_export					*insert_export(t_export *export_list,
								t_export *new_export);

t_cmd						*lst_first(t_cmd *cmd);

t_token						*first(t_token **lst);

int							is_quote(char c);
int							lstsize(t_token *lst);
int							check_error(char *str);
int							count_equals(char *str);
int							lstsize_cmd(t_cmd *cmd);
int							validator(char *prompt);
int							only_space(char *prompt);
int							ft_isall_alpha(char *str);
int							ft_is_stralnum(char *str);
int							validate_string(char *str);
int							is_flag(const char *input);
int		ft_array_len(char **array); // colocar na lib
int							check_quotes(char *prompt);
int							is_word(const char *input);
int							is_redirect(t_token *token);
int							ft_isredirect(char *string);
int							ft_isalpha_mini(char input);
int							lstsize_pipe(t_token *token);
int							is_valid_identifier(char *str);
int							ft_redirect(char *prompt, int i);
int							ft_strcmp_len(char *s1, char *s2);
int							is_operator(char chr1, char chr2);
int							ft_how_many_char(char *str, char c);
int							count_equals_chr(char *str, char c);
int							handle_quote_red(char *prompt, int *i);

char						update_quote(char quote, char current_char);

void	ft_putstring_fd(int fd); // colocar na libft
void						check_errors(t_cmd *cmd);
void						print_cmd_args(t_cmd *cmd);
void						print_tokens(t_minishell *mini);
void						print_cmd_list(t_minishell *mini);
void						shift_args(char **args, int start);
void						print_item(t_hash_item *item, int fd_out);
void						print_n_free(t_export *export, t_cmd *cmd);
void						print_export(t_hash_table *hash, t_cmd *cmd);
void						print_table(t_hash_table **table, int fd_out);

#endif
