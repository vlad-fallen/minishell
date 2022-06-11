/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:41:39 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/11 15:43:41 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home_dir(t_table_cmd *table, t_env_var	*env_list)
{
	char		*home_dir;
	t_env_var	*correct_env;
	char		*cwd;

	cwd = NULL;
	correct_env = find_key(env_list, "HOME");
	if (correct_env == NULL)
		return (EXIT_FAILURE);
	home_dir = correct_env->value;
	home_dir++;
	if (chdir(home_dir) != 0)
		return (local_cd_exit(EXIT_FAILURE, &cwd, table));
	cd_change_env("OLDPWD", NULL, env_list);
	cwd = getcwd(cwd, 0);
	cd_change_env("PWD", cwd, env_list);
	return (local_cd_exit(EXIT_SUCCESS, &cwd, table));
}

void	change_env_back(t_env_var *env_list)
{
	t_env_var	*correct_env;
	t_env_var	*correct_env_2;
	char		*tmp;

	if (check_pwd_oldpwd(env_list))
		return ;
	correct_env = find_key(env_list, "PWD");
	correct_env_2 = find_key(env_list, "OLDPWD");
	tmp = correct_env->value;
	correct_env->value = correct_env_2->value;
	correct_env_2->value = tmp;
}

int	cd_back(t_env_var *env_list, t_table_cmd *table)
{
	t_env_var	*correct_env;
	char		*cwd;
	char		*tmp;

	cwd = NULL;
	correct_env = find_key(env_list, "OLDPWD");
	if (!correct_env)
	{
		print_error("minishell", "cd", NULL, "OLDPWD not set");
		return (EXIT_FAILURE);
	}
	else
	{
		tmp = correct_env->value;
		tmp++;
		ft_putendl_fd(tmp, STDOUT_FILENO);
		if (chdir(tmp) != 0)
			return (local_cd_exit(EXIT_FAILURE, &cwd, table));
		change_env_back(env_list);
		cwd = getcwd(cwd, 0);
	}
	return (local_cd_exit(EXIT_SUCCESS, &cwd, table));
}

int	cd_fun(t_table_cmd *table)
{
	DIR			*dir;
	char		*cwd;
	t_env_var	*env_list;

	env_list = g_envp.env_list;
	cwd = NULL;
	if (table->arguments[1] == NULL)
		return (cd_home_dir(table, env_list));
	if (table->arguments[1][0] == 45)
		return (cd_back(env_list, table));
	dir = opendir(table->arguments[1]);
	if (dir == NULL)
		return (local_cd_exit(EXIT_FAILURE, &cwd, table));
	else if (closedir(dir) != 0)
		return (local_cd_exit(EXIT_FAILURE, &cwd, table));
	else if (chdir(table->arguments[1]) != 0)
		return (local_cd_exit(EXIT_FAILURE, &cwd, table));
	cd_change_env("OLDPWD", NULL, env_list);
	cwd = getcwd(cwd, 0);
	cd_change_env("PWD", cwd, env_list);
	return (local_cd_exit(EXIT_SUCCESS, &cwd, table));
}
