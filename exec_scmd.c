/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:15:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/05 19:20:45 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_scmd(t_table_cmd *table)
{
	pid_t	proc_id;
	int		stdin_dup;
	int		stdout_dup;

	stream_op(&stdin_dup, &stdout_dup, 1);
	if (execute_redirect(table))
	{
		g_envp.status_exit = 1;
		return ;
	}
	if (check_builtin(table))
	{
		run_builtin(table);
		stream_op(&stdin_dup, &stdout_dup, 2);
	}
	else
	{
		if (make_fork(&proc_id) == -1)
			return ;
		if (proc_id == 0)
			free_and_exit(exec_proc(table->arguments, g_envp.env), &table);
		exec_wait_one(proc_id);
		stream_op(&stdin_dup, &stdout_dup, 2);
		stream_op(&stdin_dup, &stdout_dup, 3);
	}
}
