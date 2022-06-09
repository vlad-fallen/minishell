/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:24:31 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/09 18:55:13 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

static void	print_value(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '$')
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
}

static void	print_declare(char *key)
{
	t_env_var	*env;

	env = g_envp.env_list;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(env->key, STDOUT_FILENO);
			if (env->value)
			{
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
				print_value(env->value);
				ft_putchar_fd('"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
			return ;
		}
		env = env->next;
	}	
}

void	print_sorted_e(t_env_var *env)
{
	char		*previous;
	char		*actual;
	t_env_var	*tmp_env_val;
	t_env_var	*tmp_val;

	tmp_env_val = env;
	if (tmp_env_val)
	{
		previous = NULL;
		while (tmp_env_val)
		{
			tmp_val = env;
			actual = NULL;
			while (tmp_val)
			{
				if ((!previous || strcmp(tmp_val->key, previous) > 0)
					&& (!actual || strcmp(tmp_val->key, actual) < 0))
					actual = tmp_val->key;
				tmp_val = tmp_val->next;
			}
			print_declare(actual);
			previous = actual;
			tmp_env_val = tmp_env_val->next;
		}
	}
}
