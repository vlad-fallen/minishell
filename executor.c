/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:26:46 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/05 18:31:39 by mbutter          ###   ########.fr       */
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

int	make_fork(pid_t *proc_id)
{
	*proc_id = fork();
	if (*proc_id == -1)
		return (-1);
	return (0);
}

void	executor(t_table_cmd *table)
{
	if (table == NULL)
		return ;
	if (table->next == NULL)
		exec_scmd(table);
	else
		exec_pipe(table);
}
