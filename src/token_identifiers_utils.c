
#include "../include/minishell.h"

int	process_token_quote(char *input, t_minishell *mini, int i, int start)
{
	int		quote_type;
	char	*substr;

	quote_type = is_quote(input[i]);
	i++;
	while (is_quote(input[i]) != quote_type)
		i++;
	substr = ft_substr(input, start + -1, i - start -1); // (-1 para tirar a outra aspas)
	add_token(substr, QUOTE, mini);
	return (i);
}

int	process_token_builtin(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != ' ' && input[i] != '\0'  && !meta_char(input[i])) // Adicionei a checagem de metachar
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, is_builtin(substr), mini);
	return (i);
}

int	process_token_word(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != ' ' && input[i] != '\0' && !meta_char(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, is_word(substr), mini);
	return (i);
}

int	process_token_arg(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != '\0' && is_arg(input + i) != 1)
		i++;
	substr = ft_substr(input, start, i);
	add_token(substr, is_arg(substr), mini);
	return (i);
}

int	process_token_operator(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (is_operator(input + i) && !ft_isalpha(input[i]))
		i++;
	substr = ft_substr(input, start, i - start);
	add_token(substr, is_operator(substr), mini);
	return (i);
}
