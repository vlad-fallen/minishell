/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:15:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/28 16:51:44 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_scmd(t_table_cmd *table)
{
	pid_t proc_id;
	int		stdin_dup;
	int		stdout_dup;

	stream_op(&stdin_dup, &stdout_dup, 1);
	execute_redirect(table);
	if (check_builtin(table))
	{
		run_builtin(table);
		stream_op(&stdin_dup, &stdout_dup, 2);
	}
	else
	{
		if (make_fork(&proc_id) == -1)
		{
			perror("make_fork");
			return ;
		}
		if (proc_id == 0)
		{
			exec_proc(table->arguments, g_envp.env);
		}
		waitpid(proc_id, NULL, 0);
		stream_op(&stdin_dup, &stdout_dup, 2);
		stream_op(&stdin_dup, &stdout_dup, 3);
	}
}
