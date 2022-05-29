/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:12:52 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/28 15:13:28 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(t_table_cmd *table)
{
	if (check_str(table->arguments[0], "echo"))
		return (1);
	if (check_str(table->arguments[0], "cd"))
		return (1);
	if (check_str(table->arguments[0], "pwd"))
		return (1);
	if (check_str(table->arguments[0], "export"))
		return (1);
	if (check_str(table->arguments[0], "unset"))
		return (1);
	if (check_str(table->arguments[0], "env"))
		return (1);
	if (check_str(table->arguments[0], "exit"))
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
