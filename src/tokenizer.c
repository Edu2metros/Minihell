#include "../include/minishell.h"

void	add_token(char *str, int type, t_minishell *mini);

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_operator(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0')
	{
		if (input[i] == '>' && input[i + 1] == '>')
			return (DOUBLE_GREAT);
		else if (input[i] == '<' && input[i + 1] == '<')
			return (DOUBLE_LESS);
		else if (input[i] == '>' && input[i + 1] != '>')
			return (GREAT);
		else if (input[i] == '<' && input[i + 1] != '<')
			return (LESS);
		else if (input[i] == '|')
			return (PIPE);
		i++;
	}
	return (1);
}

/*is_operator(char *input): Checks if a string contains shell operators like '>>',
	'<<', '>', '<',
	'|'. It returns different constants depending on the operator.*/

/* define if is random word, to use on tokenization later
its possibel to return the word, but let this part out for now */

int	is_word(const char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0' && ft_isalpha(input[i]))
	{
		while (input[i] != ' ' && input[i] != '\0')
			i++;
		return (WORD);
	}
	return (1);
}

/*is_word(const char *input): Checks if a string is a word (sequence of alphabetic characters). It returns a constant WORD if it is,
	and 1 otherwise.*/

/* define if is argument, to use on tokenization later
its possibel to return the arg, but let this part out for now */

int	is_arg(const char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '\0')
	{
		if (input[i] == '-' && ft_isalpha(input[i + 1]) == 1)
		{
			while (input[i] != ' ' && input[i] != '\0')
				i++;
			return (ARG);
		}
		i++;
	}
	return (1);
}

/*is_arg(const char *input): Checks if a string is an argument (starts with '-' followed by alphabetic characters). It returns a constant ARG if it is,
	and 1 otherwise.*/

/* thinking about do the same stuff to the commands bultins
will write the functions, then we decide if is usefull to merge
with the previous idea to make our token list*/

int	is_builtin(char *input)
{
	if (ft_strncmp(input, "echo", 4) == 0)
		return (ECHO);
	else if (ft_strncmp(input, "cd", 2) == 0)
		return (CD);
	else if (ft_strncmp(input, "pwd", 3) == 0)
		return (PWD);
	else if (ft_strncmp(input, "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(input, "unset", 5) == 0)
		return (UNSET);
	else if (ft_strncmp(input, "env", 3) == 0)
		return (ENV);
	else if (ft_strncmp(input, "exit", 4) == 0)
		return (EXIT);
	else
		return (1);
}
/*is_builtin(char *input): Checks if a string is a shell built-in command like 'echo',
	'cd', 'pwd', 'export', 'unset', 'env',
	'exit'. It returns different constants depending on the command.*/

/* this function will be used to create the token list*/

void	tokenizer(char *input, t_minishell *mini)
{
	int		i;
	int		start;
	char	*substr;

	i = 0;
	start = 0;
	while (input[i] != '\0')
	{
		if (is_quote(input[i]) == 1)
		{
			while (input[i] != '\0' && is_quote(input[i]) == 1)
				i++;
			substr = ft_substr(input, start, i);
			add_token(substr, QUOTE, mini);
		}
		else if (is_operator(input + i) != 1)
		{
			while (input[i] != '\0' && is_operator(input + i) != 1)
				i++;
			substr = ft_substr(input, start, i);
			add_token(substr, is_operator(substr), mini);
		}
		else if (is_word(input + i) != 1)
		{
			while (input[i] != '\0' && is_word(input + i) != 1)
				i++;
			substr = ft_substr(input, start, i);
			add_token(substr, is_word(substr), mini);
		}
		else if (is_arg(input + i) != 1)
		{
			while (input[i] != '\0' && is_arg(input + i) != 1)
				i++;
			substr = ft_substr(input, start, i);
			add_token(substr, is_arg(substr), mini);
		}
		else if (is_builtin(input + i) != 1)
		{
			while (input[i] != '\0' && is_builtin(input + i) != 1)
				i++;
			substr = ft_substr(input, start, i);
			add_token(substr, is_builtin(substr), mini);
		}
		else
			i++;
		start = i;
	}
}

/*tokenizer(char *input,
	t_token *token): This function tokenizes the input string. It uses the above functions to identify different types of tokens (quotes,
	operators, words, arguments,
	built-in commands) and adds them to a token list.*/

// need to change to add the token to the list making a node add function

void	add_token(char *str, int type, t_minishell *mini)
{
	t_token	*new_token;
	t_token	*last_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit(EXIT_FAILURE);
	new_token->content = ft_strdup(str);
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

// add_token(char *str, int type,
	/* t_minishell *mini): This function creates a new token with the given string and type,
	and adds it to the end of the token list in the mini shell structure.
 */
/*check with GDB where is the infinity loop*/

void print_tokens(t_minishell *mini) {
    t_token *current_token = mini->token;

    while (current_token != NULL) {
        printf("Token: %s, Type: %d\n", current_token->content, current_token->type);
        current_token = current_token->next;
    }
}



int	main(void)
{
	t_minishell	mini;
	char		*input;
	t_token		*current_token;
	t_token		*next_token;

	input = "echo 'Hello, World!' >> pwd << ksd";
	mini.token = NULL;
	tokenizer(input, &mini);
	print_tokens(&mini);
	current_token = mini.token;
	while (current_token != NULL)
	{
		next_token = current_token->next;
		free(current_token->content);
		free(current_token);
		current_token = next_token;
	}
	return (0);
}
