/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:15:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/04 20:44:34 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void exec_wait_one(int proc_id)
{
	int status;

	waitpid(proc_id, &status, 0);
	if (WIFSIGNALED(status))
	{
		g_envp.status_exit = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		g_envp.status_exit = WEXITSTATUS(status);
}

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
			free_and_exit(exec_proc(table->arguments, g_envp.env), &table);
		}
		//waitpid(proc_id, NULL, 0);
		exec_wait_one(proc_id);
		stream_op(&stdin_dup, &stdout_dup, 2);
		stream_op(&stdin_dup, &stdout_dup, 3);
	}
}
