/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:07:01 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/06 19:11:26 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_IN)
		redir->fd = open(redir->name, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		redir->fd = open(redir->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		redir->fd = open(redir->name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (redir->fd < 0)
		return (-1);
/* 	if (redir->type == REDIR_IN)
		dup2(redir->fd, STDIN_FILENO);
	else
		dup2(redir->fd, STDOUT_FILENO); */
	return (0);
}

void	heredoc_util(int *fd, t_redir *redir)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, redir->name, ft_strlen(line) - 1) == 0)
		{
			free(line);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		tmp = line;
		line = ft_strjoin(tmp, "\n");
		write(fd[1], line, ft_strlen(line));
		free(line);
		free(tmp);
	}
}

void	heredoc(t_redir *redir)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_util(fd, redir);
	}
	waitpid(pid, NULL, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

int	execute_redirect(t_table_cmd *table)
{
	t_redir	*redir_file;

	redir_file = table->redirections;
	while (redir_file != NULL)
	{
		if (redir_file->type == 4)
			heredoc(redir_file);
		else
		{
			if (open_file(redir_file) == -1)
			{
				print_error("minishell", NULL, "no such file or directory",
					redir_file->name);
				return (1);
			}
		}
		redir_file = redir_file->next;
	}
	redir_file = table->redirections;
	while(redir_file != NULL)
	{
		if (redir_file->type == REDIR_IN)
			dup2(redir_file->fd, STDIN_FILENO);
		else
			dup2(redir_file->fd, STDOUT_FILENO);
		redir_file = redir_file->next;
	}
	return (0);
}
