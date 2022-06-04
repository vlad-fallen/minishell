/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:12:52 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/04 15:34:25 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(t_table_cmd *table)
{
	if (table->arguments == NULL)
		return (0);
	if (!ft_strncmp(table->arguments[0], "echo", 5))
		return (1);
	if (!ft_strncmp(table->arguments[0], "cd", 3))
		return (1);
	if (!ft_strncmp(table->arguments[0], "pwd", 4))
		return (1);
	if (!ft_strncmp(table->arguments[0], "export", 7))
		return (1);
	if (!ft_strncmp(table->arguments[0], "unset", 6))
		return (1);
	if (!ft_strncmp(table->arguments[0], "env", 4))
		return (1);
	if (!ft_strncmp(table->arguments[0], "exit", 5))
		return (1);
	return (0);
}

void run_builtin(t_table_cmd *table)
{
	if (check_str(table->arguments[0], "echo"))
		g_envp.status_exit = echo(table);
	if (check_str(table->arguments[0], "cd"))
		g_envp.status_exit= cd(table);
	if (check_str(table->arguments[0], "pwd"))
		g_envp.status_exit = pwd();
	if (check_str(table->arguments[0], "export"))
		g_envp.status_exit = export_fun(table);
	if (check_str(table->arguments[0], "unset"))
		g_envp.status_exit = unset_fun(table);
	if (check_str(table->arguments[0], "env"))
		g_envp.status_exit = env();
	if (check_str(table->arguments[0], "exit"))
		g_envp.status_exit = exit_prog(table);
}
