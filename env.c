/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:41:34 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/19 15:11:05 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env(void)
{
    t_env_var	*env_init_tmp;

	env_init_tmp = g_envp.env_list;

    if (!env_init_tmp)
    {
        ft_putstr_fd("env is not find (=NULL)\n", 2);
        return (EXIT_FAILURE);
    }
    print_list_env(env_init_tmp);
    return (EXIT_SUCCESS);
}