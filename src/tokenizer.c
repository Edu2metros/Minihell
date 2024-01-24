#include "../include/minishell.h"

int	process_token_quote (char *input, t_minishell *mini, int i, int start)
{
	int		quote_type;
	char	*substr;

	quote_type = is_quote(input[i]);
	i++;
	while (is_quote(input[i]) != quote_type )
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, QUOTE, mini);
	return (i);
}

int	process_token_builtin(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != ' ')
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, is_builtin(substr), mini);
	return (i);
}

void	tokenizer(char *input, t_minishell *mini)
{
	int		i;
	int		start;
	int		quote_type;
	char	*substr;

	i = 0;
	start = 0;
	while (input[i] != '\0')
	{
		while (input[i] == ' ')
		{	
			i++;
			start++;
		}
		if (is_quote(input[i]) != 1)
		{
			quote_type = is_quote(input[i]);
			i++;
			while (is_quote(input[i]) != quote_type )
				i++;
			substr = ft_substr(input, start, i - start);
			add_token(substr, QUOTE, mini);
			if (input[i] != '\0')
				i++;
			if (input[i] != '\0')
				i++;
		}
		else if (is_builtin(input + i) != 1)
		{
			while (input[i] != ' ')
				i++;
			substr = ft_substr(input, start, i - start);
			add_token(substr, is_builtin(substr), mini);
		}
		else if (is_word(input + i) != 1)
		{
			while (input[i] != ' ')
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
		else if (is_operator(input + i) != 1 && is_operator(input + i) != 0)
		{
			while (is_operator(input + i) != 1)
				i++;
			substr = ft_substr(input, start, i - start + 1);
			add_token(substr, is_operator(substr), mini);
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
        printf("Token: %s: Type: %d\n\n", current_token->content, current_token->type);
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