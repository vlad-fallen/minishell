/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:44:24 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/12 12:50:35 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_wait_one(int proc_id)
{
	int	status;

	waitpid(proc_id, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 2);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
		g_envp.status_exit = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		g_envp.status_exit = WEXITSTATUS(status);
}

void	exec_wait_all(int proc_id, int *stdin_dup, int *stdout_dup)
{
	exec_wait_one(proc_id);
	stream_op(stdin_dup, stdout_dup, 2);
	while (wait(NULL) != -1)
		stream_op(stdin_dup, stdout_dup, 2);
	stream_op(stdin_dup, stdout_dup, 3);
}
