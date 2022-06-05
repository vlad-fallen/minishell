/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:30:52 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/05 19:04:07 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe_fd(int **pipe_fd)
{
	(*pipe_fd) = (int *)malloc(2 * sizeof(int));
	if ((*pipe_fd) == NULL)
		return (1);
	return (0);
}

int	pipe_found(t_table_cmd *table, int **pipe_fd)
{
	int	status;

	status = 0;
	if (table->next != NULL)
	{
		status = pipe(*pipe_fd);
		if (status == -1)
			return (-1);
		return (1);
	}
	return (status);
}

void	exec_child_proc(int **pipe_fd, t_table_cmd **table, int pipe_flag)
{
	if (pipe_flag == 1)
	{
		close((*pipe_fd)[0]);
		dup2((*pipe_fd)[1], STDOUT_FILENO);
		close((*pipe_fd)[1]);
	}
	if (execute_redirect(*table))
	{
		free(*pipe_fd);
		*pipe_fd = NULL;
		free_and_exit(1, table);
	}
	if (*pipe_fd != NULL)
	{
		free(*pipe_fd);
		*pipe_fd = NULL;
	}
	if (check_builtin(*table))
	{
		run_builtin(*table);
		exit(g_envp.status_exit);
	}
	else
		free_and_exit(exec_proc((*table)->arguments, g_envp.env), table);
}

void	exec_parent_proc(int pipe_flag, int **pipe_fd)
{
	if (pipe_flag == 1)
	{
		close((*pipe_fd)[1]);
		dup2((*pipe_fd)[0], STDIN_FILENO);
		close((*pipe_fd)[0]);
	}
}

void	exec_pipe(t_table_cmd *table)
{
	pid_t	proc_id;
	int		*pipe_fd;
	int		pipe_flag;
	int		stdin_dup;
	int		stdout_dup;

	if (init_pipe_fd(&pipe_fd))
		return ;
	stream_op(&stdin_dup, &stdout_dup, 1);
	while (table != NULL)
	{
		pipe_flag = pipe_found(table, &pipe_fd);
		if (pipe_flag == -1 || make_fork(&proc_id) == -1)
			return ;
		if (proc_id == 0)
			exec_child_proc(&pipe_fd, &table, pipe_flag);
		else if (proc_id > 0)
			exec_parent_proc(pipe_flag, &pipe_fd);
		table = table->next;
	}
	free(pipe_fd);
	exec_wait_all(proc_id, &stdin_dup, &stdout_dup);
}
