/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:55:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/21 18:10:42 by echrysta         ###   ########.fr       */
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


static void	print_declare(char *key)
{
	t_env_var *env;
	
	env = g_envp.env_list;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd(env->value, 1);
			ft_putchar_fd('\n', 1);
			return ;
		}
		env = env->next;
	}	
}

static void	print_sorted_e(t_env_var *env)
{
	char	*previous;
	char	*actual;
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

static t_env_var	*envlist_new_alone(char	*key)
{
	t_env_var	*list;

	list = (t_env_var *)malloc(sizeof(t_env_var));
	if (list != NULL)
	{
		list->key = ft_strdup(key);
		list->value = NULL;
		list->next = NULL;
	}
	return (list);
}

static int	check_argc(char *str)
{
	char ch;

	ch = str[0];
	if (!(97 <= ch && ch <= 122) && !(65 <= ch && ch <= 90))
	{
		ft_putstr_fd("zhs: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	add_elem_env(char *str, t_env_var *env_list)
{
	t_env_var	*new_env_list;
	char		*key;
	char		*value;
	int			i;

	key = NULL;
	value = NULL;
	i = 0;
	if (check_argc(str))
		return (EXIT_FAILURE);
	while (str[i] != '=' && str[i] != '\0')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		key[i] = str[i];
		i++;
	}
	if (str[i] != '\0')
		value = strdup(&str[i]);
	while (env_list->next)
		env_list = env_list->next;
	if (value != NULL)
		new_env_list = envlist_new(key, value);
	else
		new_env_list = envlist_new_alone(key);
	envlist_add_back(&env_list, new_env_list);
	return (EXIT_SUCCESS);
}

int	export_fun(t_table_cmd *table)
{
	t_env_var	*env_list;
	int			i;

	env_list = g_envp.env_list;
	if (!table->arguments[1])
	{
			print_sorted_e(g_envp.env_list);
		return (EXIT_SUCCESS);
	}
	i = 1;
	while (table->arguments[i])
	{
		if (add_elem_env(table->arguments[i], env_list))
			return (EXIT_FAILURE);
		i++;
	}
	return(EXIT_SUCCESS);
}