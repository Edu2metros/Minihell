#include "../include/minishell.h"
#include <readline/history.h>

int	mini_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && (unsigned char)c != s[i])
		i++;
	if ((unsigned char)c == s[i])
		return (i);
	return (-1);
}

int	mini_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0 && (unsigned char)c != s[i])
		i--;
	if ((unsigned char)c == s[i])
		return (i);
	return (-1);
}

int	identify_quote(char *string)
{
	while (*string && *string != '\'' && *string != '"')
		string++;
	return (*string);
}

char	*extract_string_quote(char *string)
{
	char	quote;

	quote = identify_quote(string);
	return (ft_substr(string, mini_strchr(string, quote), mini_strrchr(string,
				quote) + 1));
}