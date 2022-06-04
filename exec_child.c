/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:05:14 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/04 16:27:30 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_util(char **path_envp, char *cmd)
{
	char	*part_path;
	char	*path;
	int		i;
	
	i = -1;
	part_path = ft_strjoin("/", cmd);
	while (path_envp[++i])
	{
		path = ft_strjoin(path_envp[i], part_path);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free(part_path);
	arr_free(&path_envp);
	return (path);
}

char	*find_path(char *cmd, char **envp)
{
	char	**path_envp;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
	{
		if (envp[i] == NULL)
			return (NULL);
		i++;
	}
	path_envp = ft_split(envp[i] + 5, ':');
	return (find_path_util(path_envp, cmd));
}

int	exec_proc(char **cmd, char **envp)
{
	char		*path;
	struct stat	buf;
	int			exit_stat;

	if (cmd == NULL)
		exit(EXIT_SUCCESS);
	if (!ft_strchr(cmd[0], '/'))
		path = find_path(cmd[0], envp);
	else
		path = cmd[0];
	execve(path, cmd, envp);
	exit_stat = 0;
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		print_error("minishell", cmd[0], NULL, "permision denied");
		exit_stat = 126;
	}
	else if (stat(cmd[0], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			print_error("minishell", cmd[0], NULL, "is a directory");
			exit_stat = 126;
		}
	}
	else
	{
		print_error("minishell", cmd[0], NULL, "no such file or directory");
		exit_stat = 127;
	}
	return (exit_stat);
}
