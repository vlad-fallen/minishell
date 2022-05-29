/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:26:46 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/29 16:27:57 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stream_op(int *initial_stdin, int *initial_stdout, int mode)
{
	if (mode == 1)
	{
		*initial_stdin = dup(STDIN_FILENO);
		*initial_stdout = dup(STDOUT_FILENO);
	}
	else if (mode == 2)
	{
		dup2(*initial_stdin, STDIN_FILENO);
		dup2(*initial_stdout, STDOUT_FILENO);
	}
	else if (mode == 3)
	{
		close(*initial_stdin);
		close(*initial_stdout);
	}
}

int make_fork(pid_t *proc_id)
{
	*proc_id = fork();
	if (*proc_id == -1)
		return (-1);
	return (0);
}

/*--------------------EXEC_PIPE-------------------------*/

/* int	init_pipe_fd(t_table_cmd **table)
{
	int fd_pipe[2];
	t_table_cmd *tmp_table;

	tmp_table = *table;
	tmp_table->stream_in = dup(STDIN_FILENO);
	while (tmp_table->next != NULL)
	{
		if (pipe(fd_pipe) == -1)
			return (-1);
		tmp_table->stream_out = fd_pipe[1];
		tmp_table = tmp_table->next;
		tmp_table->stream_in = fd_pipe[0];
	}
	tmp_table->stream_out = dup(STDOUT_FILENO);
	return (0);
	
} */

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

void exec_pipe(t_table_cmd *table)
{
	pid_t	proc_id;
	int		*pipe_fd;
	int		pipe_flag;
	int		stdin_dup;
	int		stdout_dup;
	
	//if (init_pipe_fd(&table))
	if (init_pipe_fd(&pipe_fd))
		return ;
	stream_op(&stdin_dup, &stdout_dup, 1);
	while (table != NULL)
	{
		pipe_flag = pipe_found(table, &pipe_fd);
		if (pipe_flag == -1 || make_fork(&proc_id) == -1)
			return ;
		if (proc_id == 0)
		{
			//if (table->next != NULL)
			if (pipe_flag == 1)
			{
				/* close(table->stream_in);
				dup2(table->stream_out, STDOUT_FILENO);
				close(table->stream_out); */
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			execute_redirect(table);
			if (pipe_fd != NULL)
			{
				free(pipe_fd);
				pipe_fd = NULL;
			}
			if (check_builtin(table))
			{
				run_builtin(table);
			}
			else
			{
				exec_proc(table->arguments, g_envp.env);
			}
		}
		else if (proc_id > 0)
		{
			//if (table->next != NULL)
			if (pipe_flag == 1)
			{
				/* close(table->stream_out);
				dup2(table->stream_in, STDIN_FILENO);
				close(table->stream_in); */
				close(pipe_fd[1]);
				dup2(pipe_fd[0], STDIN_FILENO);
				close(pipe_fd[0]);
			}
		}
		table = table->next;
	}
	free(pipe_fd);
	waitpid(proc_id, NULL, 0);
	//wait(NULL);
	stream_op(&stdin_dup, &stdout_dup, 2);
	while (wait(NULL) != -1)
		stream_op(&stdin_dup, &stdout_dup, 2);
	stream_op(&stdin_dup, &stdout_dup, 3);
}

/*--------------------EXECUTOR(main function)-------------------------*/

void executor(t_table_cmd *table)
{
	if (table == NULL)
		return ;
	if (table->next == NULL)
		exec_scmd(table);
	else
		exec_pipe(table);
}