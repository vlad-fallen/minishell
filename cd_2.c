/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:01:50 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/05 15:02:46 by echrysta         ###   ########.fr       */
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
