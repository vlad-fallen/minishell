/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:10:14 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/10 21:11:23 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	local_cd_exit(int exit_status, char **cwd, t_table_cmd *table)
{
	free(*cwd);
	*cwd = NULL;
	if (exit_status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
	{
		ft_putstr_fd("zhs: cd: ", 2);
		perror(table->arguments[1]);
		return (EXIT_FAILURE);
	}
}

t_env_var	*find_key(t_env_var	*env_init_tmp, char *which_pwd)
{
	t_env_var	*tmp;

	tmp = env_init_tmp;
	while (tmp)
	{
		if (ft_strlen(tmp->key) == ft_strlen(which_pwd))
		{
			if (check_str(tmp->key, which_pwd))
				break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}
