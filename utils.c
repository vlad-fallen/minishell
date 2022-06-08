/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:51:58 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/08 14:26:04 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *shell_name, char *cmd, char *arg, char *message)
{
	if (shell_name != NULL)
	{
		ft_putstr_fd(shell_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (message != NULL)
	{
		ft_putstr_fd(message, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	arr_free(char ***arr)
{
	size_t	i;
	char	**tmp;

	tmp = *arr;
	i = 0;
	if (tmp == NULL)
		return ;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	free_and_exit(int status, t_table_cmd **table)
{
	free_global_env();
	free_table(table);
	exit(status);
}
