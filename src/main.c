#include "../include/minishell.h"
#include <readline/history.h>

int	check_quote(char *input)
{
	int		i;
	char	type;

	i = 0;
	type = 0;
	while (*input != '\0')
	{
		if (*input == '\'' || *input == '"')
			break ;
		input++;
	}
	if (!*input)
		return (2);
	type = *input;
	while (*input != '\0')
	{
		if (*input == type)
			i++;
		input++;
	}
	return (i % 2 == 0);
}

void	add_token(char *str, int type, t_minishell *mini)
{
	t_token	*new_token;
	t_token	*last_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit(EXIT_FAILURE);
	if (ft_strlen(str) == 2)
		new_token->content = ft_strdup(str);
	else
		new_token->content = str;
	new_token->type = type;
	new_token->next = NULL;
	if (mini->token)
	{
		last_token = mini->token;
		while (last_token->next != NULL)
			last_token = last_token->next;
		last_token->next = new_token;
	}
	else
		mini->token = new_token;
}

int	check_meta(char *input, t_minishell *mini)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(">>", DOUBLE_GREAT, mini);
			i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token("<<", DOUBLE_LESS, mini);
			i++;
		}
		else if (input[i] == '>' && input[i + 1] != '>')
			add_token(">", GREAT, mini);
		else if (input[i] == '<' && input[i + 1] != '<')
			add_token("<", LESS, mini);
		else if (input[i] == '|')
			add_token("|", PIPE, mini);
		i++;
	}
	return (1);
}

void	handle_error(int nbr)
{
	static char *message[2] = {
		"Please close the quotes.",
		"Syntax error.",
	};
	printf("%s\n", message[nbr]);
}

void	validator(char *prompt)
{
	int	i;

	if (prompt[0] == '|' || prompt[ft_strlen(prompt) - 1] == '|')
		handle_error(1);
	if (!ft_strncmp(prompt, ">>", 2) || !ft_strncmp(prompt, ">", 1))
	{
		i = mini_strrchr(prompt, '>') + 1;
		while(prompt[i] != '\0' && my_isspace(prompt[i]))
			i++;
		if(prompt[i] == '\0' || my_isspace(prompt[i]))
			handle_error(1);
	}
}

int	main(void)
{
	char		*prompt;
	t_minishell	*mini;

	mini = ft_calloc(1, sizeof(t_minishell));
	mini->token = ft_calloc(1, sizeof(t_token));
	while (1)
	{
		prompt = readline("Minishell $> ");
		add_history(prompt);
		validator(prompt);
		// lexer(prompt, mini);
	}
	clear_history();
}

/*
pipe não começa nem termina
verificar redirect, sempre seguido com nome de arquivo
 */
