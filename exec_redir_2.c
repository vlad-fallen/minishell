/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:30:55 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/11 17:31:20 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_redirect_help(t_redir *redir_file, t_table_cmd *table)
{
	redir_file = table->redirections;
	while (redir_file != NULL)
	{
		if (redir_file->type == REDIR_IN)
			dup2(redir_file->fd, STDIN_FILENO);
		else
			dup2(redir_file->fd, STDOUT_FILENO);
		redir_file = redir_file->next;
	}
}
