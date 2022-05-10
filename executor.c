/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:26:46 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/10 15:29:00 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arr_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

char	*find_path(char *cmd, char **envp)
{
	char	**path_envp;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	path_envp = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_envp[i])
	{
		part_path = ft_strjoin(path_envp[i++], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			arr_free(path_envp);
			return (path);
		}
		free(path);
	}
	arr_free(path_envp);
	return (NULL);
}

void	exec_proc(char **cmd, char **envp)
{
	char	*path;

	if (!ft_strchr(cmd[0], '/'))
	{
		path = find_path(cmd[0], envp);
		execve(path, cmd, envp);
	}
	else
	{
		path = cmd[0];
		if (access(path, F_OK) == 0)
			execve(path, cmd, envp);
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
	exit(EXIT_FAILURE);
}

int make_fork(pid_t *proc_id)
{
	*proc_id = fork();
	if (*proc_id == -1)
		return (-1);
	return (0);
}

int	check_builtin(t_table_cmd *table)
{
	if (check_str(table->commands->arguments[0], "echo"))
		return (1);
	if (check_str(table->commands->arguments[0], "cd"))
		return (1);
	if (check_str(table->commands->arguments[0], "pwd"))
		return (1);
	if (check_str(table->commands->arguments[0], "export"))
		return (1);
	if (check_str(table->commands->arguments[0], "unset"))
		return (1);
	if (check_str(table->commands->arguments[0], "env"))
		return (1);
	if (check_str(table->commands->arguments[0], "exit"))
		return (1);
	return (0);
}

void run_builtin(t_table_cmd *table)
{
	if (check_str(table->commands->arguments[0], "echo"))
		echo(table);
	// if (check_str(table->commands->arguments[0], "cd"))
	// 	cd(table);
	// if (check_str(table->commands->arguments[0], "pwd"))
	// 	pwd(table);
	// if (check_str(table->commands->arguments[0], "export"))
	// 	export(table);
	// if (check_str(table->commands->arguments[0], "unset"))
	// 	unset(table);
	// if (check_str(table->commands->arguments[0], "env"))
	// 	env(table);
	// if (check_str(table->commands->arguments[0], "exit"))
	// 	exit(table);
}

void executor(t_table_cmd *table)
{
	pid_t proc_id;

	if (make_fork(&proc_id) == -1)
	{
		perror("make_fork");
		return ;
	}
	if (proc_id == 0)
	{
		if(check_builtin(table))
			run_builtin(table);
		else
			exec_proc(table->commands->arguments, g_envp.env);
	}
	waitpid(proc_id, NULL, 0);
}