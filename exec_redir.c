/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:07:01 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/11 17:31:16 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_in_env(char *value, int flag_ex);

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
	return (0);
}

void	heredoc_util(int *fd, t_redir *redir)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, redir->name, ft_strlen(line) + 1))
		{
			free(line);
			if (!line)
				write(1, "\n", 1);
			break ;
		}
		tmp = line;
		line = ft_strjoin(tmp, "\n");
		ft_putstr_fd(line, *fd);
		free(line);
		free(tmp);
	}
}

int	init_heredoc(char **filename, int *fd)
{
	*filename = ft_strdup(".heredoc_tmp");
	*fd = open(*filename, O_CREAT | O_APPEND | O_RDWR, 0600);
	if (*fd == -1)
	{
		unlink(*filename);
		print_error("minishell", "heredoc", strerror(errno), *filename);
		free(*filename);
		*filename = NULL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	heredoc(t_redir **redir)
{
	char	*filename;

	if (init_heredoc(&filename, &(*redir)->fd))
		return ;
	heredoc_util(&(*redir)->fd, *redir);
	close((*redir)->fd);
	(*redir)->fd = open(filename, O_RDONLY);
	(*redir)->type = REDIR_IN;
	unlink(filename);
	free(filename);
	filename = NULL;
}

int	execute_redirect(t_table_cmd *table)
{
	t_redir	*redir_file;

	redir_file = table->redirections;
	while (redir_file != NULL)
	{
		if (redir_file->type == 4)
			heredoc(&redir_file);
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
	execute_redirect_help(redir_file, table);
	return (0);
}
