/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:41:34 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/14 14:47:25 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env(void)
{
    t_env_var	*env_init_tmp;

	env_init_tmp = g_envp.env_list;
    print_list_env(env_init_tmp);
    return (EXIT_SUCCESS);
}