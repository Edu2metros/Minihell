/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:03 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/01/09 14:48:47 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define GREAT 1
# define LESS 2
# define PIPE 3
# define QUOTE 4
# define DOUBLE_QUOTE 5
# define DOUBLE_GREAT 6
# define DOUBLE_LESS 7

# include "./libft/libft.h"

typedef struct s_minishell
{
	char	**path;

}			t_minishell;
int			ft_isalldigit_minishell(const char *str);
#endif
