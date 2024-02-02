/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:42:42 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/29 18:19:07 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Process when you have the '$' token
// but I have a doubt, what would be the limit? space?

#include "../../include/minishell.h"

int	process_token_dollar(char *input, t_minishell *mini, int i, int start)
{
	char	*substr;

	while (input[i] != '\0' && ft_isalpha(input[i]))
		i++;
	substr = ft_substr(input, start, i);
	add_token(substr, DOLLAR, mini);
	return (i);
}