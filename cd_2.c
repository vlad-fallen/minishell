/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:37:41 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/11 15:45:03 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pwd_oldpwd(t_env_var *env_list)
{
	t_env_var	*correct_env;
	t_env_var	*correct_env_2;

	correct_env = find_key(env_list, "PWD");
	correct_env_2 = find_key(env_list, "OLDPWD");
	if (check_str(correct_env->value, correct_env_2->value))
		return (1);
	return (0);
}

void	cd_change_env_old(t_env_var *env_list)
{
	t_env_var	*correct_env;
	t_env_var	*correct_env_2;
	char		*new_value;
	char		*oldpwd;

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

void	cd_change_env(char *which_pwd, char *value, t_env_var *env_list)
{
	t_env_var	*correct_env;
	char		*new_value;

	if (check_str(which_pwd, "PWD"))
	{
		correct_env = find_key(env_list, "PWD");
		free(correct_env->value);
		correct_env->value = NULL;
		new_value = ft_strjoin("=", value);
		correct_env->value = new_value;
	}
	if (check_str(which_pwd, "OLDPWD"))
		cd_change_env_old(env_list);
}
