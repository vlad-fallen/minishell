/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:55:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/14 16:10:32 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_def_evn_exp(t_env_var *env_list)
{
	int i;

	while (env_list)
	{
		i = 1;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_list->key, 1);
		if (env_list->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			while (env_list->value[i])
			{
				ft_putchar_fd(env_list->value[i], 1);
				i++;
			}
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		env_list = env_list->next;
	}
}

t_env_var	*envlist_new_alone(char	*key)
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

int	check_argc(char *str)
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

int	add_elem_env(char *str, t_env_var *env_list)
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
		print_def_evn_exp(env_list);
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