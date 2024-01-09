#include "../include/minishell.h"

int	ft_isalldigit_minishell(const char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	while (*str)
		if (!ft_isalpha(*str++))
			return (0);
	return (1);
}