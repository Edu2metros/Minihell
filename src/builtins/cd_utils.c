
#include "../../include/minishell.h"

int	ft_how_many_char(char *str, char c)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			result++;
		i++;
	}
	return (result);
}