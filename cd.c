/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:41:39 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/14 18:07:54 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	local_cd_exit(int exit_status, char **cwd)
{
	free(*cwd);
	*cwd = NULL;
	if (exit_status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
}

t_env_var	*find_key(t_env_var	*env_init_tmp, char *which_pwd)
{
	while (env_init_tmp)
	{
		if (check_str(env_init_tmp->key, which_pwd))
			break ;
		env_init_tmp = env_init_tmp->next;
	}
	return (env_init_tmp);
}

void	change_env(char *which_pwd, char *value)
{
	t_env_var	*env_init_tmp;
	t_env_var	*correct_env;
	char		*new_value;

	env_init_tmp = g_envp.env_list;
	if (check_str(which_pwd, "OLDPWD"))
	{
		correct_env = find_key(env_init_tmp, which_pwd);
		free(env_init_tmp->value);
		correct_env = find_key(env_init_tmp, "PWD");
		new_value = ft_strdup(correct_env->value);
		env_init_tmp->value = new_value;
	}
	if (check_str(which_pwd, "PWD"))
	{
		correct_env = find_key(env_init_tmp, which_pwd);
		free(env_init_tmp->value);
		new_value = ft_strdup(value);
		env_init_tmp->value = new_value;
    }
}

char	*without_ravno(char *str)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char)*ft_strlen(str));
	i = 0;
	while (str[i] != '\0')
	{
		new_str[i] = str[i+1];
		i++;
	}
	free(str);
	return (new_str);
}

int cd_home_dir()
{
	char	*home_dir;
	t_env_var   *correct_env;
	t_env_var   *env_init_tmp;
	char	*cwd;

	cwd = NULL;
	env_init_tmp = g_envp.env_list;
	correct_env = find_key(env_init_tmp, "HOME");
	home_dir = correct_env->value;
	if (home_dir == NULL)
		return (EXIT_FAILURE);
	home_dir = without_ravno(home_dir);
	if (chdir(home_dir) != 0)
	{
		free(home_dir);
		return (local_cd_exit(EXIT_FAILURE, &cwd));
	}
	change_env("OLDPWD", NULL);
	cwd = getcwd(cwd, 0);
	change_env("PWD", cwd);
	free(home_dir);
	return (local_cd_exit(EXIT_SUCCESS, &cwd));
}

int	cd(t_table_cmd *table)
{
	DIR		*dir;
	char	*cwd;

	cwd = NULL;
	if (table->arguments[1] == NULL)
		return (cd_home_dir());
	dir = opendir(table->arguments[1]);
	if (dir == NULL)
		return (local_cd_exit(EXIT_FAILURE, &cwd));
	else if (closedir(dir) != 0)
		return (local_cd_exit(EXIT_FAILURE, &cwd));
	else if (chdir(table->arguments[1]) != 0)
		return (local_cd_exit(EXIT_FAILURE, &cwd));
	change_env("OLDPWD", NULL);
	cwd = getcwd(cwd, 0);
	change_env("PWD", cwd);
	return(local_cd_exit(EXIT_SUCCESS, &cwd));
}