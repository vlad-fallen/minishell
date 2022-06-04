/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:07:01 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/04 20:52:39 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_file(t_redir *redir)
{
	int fd;

	fd = -1;
	if (redir->type == REDIR_IN)
		fd = open(redir->name, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		return (-1);
	}
	if (redir->type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
	{
		dup2(fd, STDOUT_FILENO);
	}
	return (0);
}

void	heredoc_util(int *fd, t_redir *redir)
{
	char	*line;
	char	*tmp;
	int		quote_flag;
	char	*limiter;
	
	quote_flag = 0;
	limiter = redir->name;
	if (redir->name[0] == '"')
	{
		limiter += 1;
		quote_flag = 1;
	}
	while (1)
	{
		//write(1, "> ", 2);
		//line = get_next_line(STDIN_FILENO);
		line = readline("> ");
		if (ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		tmp = line;
		if (quote_flag == 0)
			tmp = change_in_env(tmp, 0);
		line = ft_strjoin(tmp, "\n");
		write(fd[1], line, ft_strlen(line));
		free(line);
		free(tmp);
	}
}

void heredoc(t_redir *redir)
{
/* 	char	*line;
	char	*tmp; */
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return ; //!!!make return error!!!
	pid = fork();
	if (pid < 0)
		return ; //!!!make return error!!!
	if (pid == 0)
	{
		close(fd[0]);
		//dup2(fd[1], STDOUT_FILENO);
		heredoc_util(fd, redir);
		/* while (1)
		{
			//write(1, "> ", 2);
			//line = get_next_line(STDIN_FILENO);
			line = readline("> ");
			if (ft_strncmp(line, redir->name, ft_strlen(line) - 1) == 0)
			{
				free(line);
				close(fd[1]);
				exit(EXIT_SUCCESS);
			}
			tmp = line;
			tmp = change_in_env(tmp, 0);
			line = ft_strjoin(tmp, "\n");
			write(fd[1], line, ft_strlen(line));
			free(line);
			free(tmp);
		} */
	}
	waitpid(pid, NULL, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void execute_redirect(t_table_cmd *table)
{
	t_redir *redir_file;

	redir_file = table->redirections;
	while (redir_file != NULL)
	{
		if (redir_file->type == 4)
		{
			heredoc(redir_file);
		}
		else
		{
			if (open_file(redir_file) == -1)
			{
				return ;
			}
		}
		//printf("1\n");
		redir_file = redir_file->next;
	}
}
