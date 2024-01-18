#include <stdlib.h>
#include <string.h>

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

	i = strlen(s) - 1;
	while (i >= 0 && (unsigned char)c != s[i])
		i--;
	if ((unsigned char)c == s[i])
		return (i);
	return (-1);
}

char	identify_quote(char *string)
{
	while (*string && *string != '\'' && *string != '"')
		string++;
	return (*string);
}

char	*extract_string_quote(char *string)
{
	char	*result;
	char	quote;
	int		start;
	int		last;

	quote = identify_quote(string);
	start = mini_strchr(string, quote) + 1; // Skip the opening quote
	last = mini_strrchr(string, quote);
	if (start >= 0 && last >= 0 && last >= start)
	{
		result = malloc(last - start + 1); // Allocate memory for the substring
		if (result != NULL)
		{
			strncpy(result, string + start, last - start); // Copy the substring
			result[last - start] = '\0';                  
				// Null-terminate the string
		}
	}
	else
	{
		result = malloc(1); // Allocate memory for an empty string
		if (result != NULL)
			result[0] = '\0';
	}
	return (result);
}

/* // Example usage
#include <stdio.h>

int	main(void)
{
	char	*extracted;

	char original[] = ""
						"\"oii\""
						"";
	extracted = extract_string_quote(original);
	printf("Original: %s\n", original);
	printf("Extracted: %s\n", extracted);
	free(extracted); // Don't forget to free the allocated memory
	return (0);
} */
