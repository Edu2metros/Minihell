/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:14:43 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/15 19:21:18 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    validate_numeric_string(char *str, int *code_status)
{
    int    i;

    i = 0;
    while (str[i])
    {
        if (i == 0 && (str[0] == '+' || str[0] == '-'))
            i++;
        if (ft_isdigit(str[i]) == 0)
        {
            printf("bash: exit: %s: numeric argument required\n", str);
            *code_status = 2;
            break ;
        }
        i++;
    }
    if (str[i] == '\0')
        *code_status = ft_atol(str);
    return (*code_status);
}

void    free_exit(t_minishell *mini, t_hash_table **table, int status)
{
    free_table(table);
    free_all(mini);
	printf("exit\n");
    exit(status);
}

void    ft_exit(t_cmd *node, t_hash_table **table)
{
    int    i;
    int    code_status;

    i = 1;
    code_status = 0;
    while (node->args[i] != NULL)
    {
        if (i > 1)
        {
			ft_printf_fd(2, "bash: exit: too many arguments\n");
            get_control()->return_status = 1;
            return ;
        }
        if (validate_numeric_string(node->args[1], &code_status) == 2)
            return ;
        i++;
    }
    free_exit(get_control(), table, code_status);
    exit(code_status);
}

