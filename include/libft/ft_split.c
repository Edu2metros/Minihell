/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:13:44 by eddos-sa          #+#    #+#             */
/*   Updated: 2023/08/10 13:11:52 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c);
static char		*create_word(const char **s, char c);

char	**ft_split(char const *string, char chr)
{
	size_t	words;
	size_t	i;
	char	**result;

	words = count_words(string, chr);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*string && words > 0)
	{
		if (chr == *string)
			string++;
		else
		{
			result[i++] = create_word(&string, chr);
			words--;
		}
	}
	result[i] = NULL;
	return (result);
}

static size_t	count_words(const char *s, char c)
{
	size_t	words_number;

	words_number = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			words_number++;
			while (*s && *s != c)
				s++;
		}
	}
	return (words_number);
}

static char	*create_word(const char **s, char c)
{
	const char	*start;
	size_t		size;
	char		*new_word;
	const char	*src;
	char		*dst;

	start = *s;
	while (**s && **s != c)
		(*s)++;
	size = *s - start;
	new_word = (char *)malloc((size + 1) * sizeof(char));
	if (!new_word)
		return (NULL);
	src = start;
	dst = new_word;
	while (src < *s)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (new_word);
}
