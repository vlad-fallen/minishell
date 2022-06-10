/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:41:39 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/10 18:03:01 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	local_cd_exit(int exit_status, char **cwd, t_table_cmd *table)
{
	free(*cwd);
	*cwd = NULL;
	if (exit_status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
	{
		ft_putstr_fd("zhs: cd: ", 2);
		perror(table->arguments[1]);
		return (EXIT_FAILURE);
	}
}

t_env_var	*find_key(t_env_var	*env_init_tmp, char *which_pwd)
{
	t_env_var	*tmp;

	tmp = env_init_tmp;
	while (tmp)
	{
		if (ft_strlen(tmp->key) == ft_strlen(which_pwd))
		{
			if (check_str(tmp->key, which_pwd))
				break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

void	cd_change_env(char *which_pwd, char *value, t_env_var *env_list)
{
	t_env_var	*correct_env;
	t_env_var	*correct_env_2;
	char		*new_value;
	char		*oldpwd;


	if (check_str(which_pwd, "PWD"))
	{
		correct_env = find_key(env_list, "PWD");
		free(correct_env->value);
		correct_env->value = NULL;
		new_value = ft_strjoin("=", value);
		correct_env->value = new_value;
	}
	if (check_str(which_pwd, "OLDPWD"))
	{
		correct_env = find_key(env_list, "OLDPWD");
		if (correct_env)
		{
			free(correct_env->value);
			correct_env->value = NULL;
			correct_env_2 = find_key(env_list, "PWD");
			new_value = ft_strdup(correct_env_2->value);
			correct_env->value = new_value;
		}
		else
		{
			correct_env_2 = find_key(env_list, "PWD");
			new_value = ft_strdup(correct_env_2->value);
			oldpwd = ft_strdup("OLDPWD");
			add_elem_env_help(env_list, oldpwd, new_value);
		}
	}
}

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
	//cd_change_env("OLDPWD", NULL, env_list);
	cwd = getcwd(cwd, 0);
	//cd_change_env("PWD", cwd, env_list);
	return (local_cd_exit(EXIT_SUCCESS, &cwd, table));
}

int	cd_back(t_env_var *env_list, t_table_cmd *table)
{
	t_env_var	*correct_env;
	char		*cwd;
		
	cwd = NULL;
	correct_env = find_key(env_list, "OLDPWD");
	if (!correct_env)
	{
		print_error("minishell", "cd", NULL,"OLDPWD not set");
		return (EXIT_FAILURE);
	}
	else
	{
		correct_env->value++;
		ft_putendl_fd(correct_env->value, STDOUT_FILENO);
		if (chdir(correct_env->value) != 0)
			return (local_cd_exit(EXIT_FAILURE, &cwd, table));
		//cd_change_env("OLDPWD", NULL, env_list);
		cwd = getcwd(cwd, 0);
		//cd_change_env("PWD", cwd, env_list);
	}
	return(local_cd_exit(EXIT_SUCCESS, &cwd, table));
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
