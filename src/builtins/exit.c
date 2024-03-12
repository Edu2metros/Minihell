/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:14:43 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/12 12:32:29 by jaqribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_exit(t_cmd *cmd, char *status)
{
	int i;
	i = ft_atol(status); // long long int
	printf("exit\n");
	get_control()->return_status = i;
}
