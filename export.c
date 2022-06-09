/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:55:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/09 18:51:42 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_elem_env_help(t_env_var *env_list, char *key, char *value)
{	
	t_env_var	*new_env_list;

	while (env_list->next)
		env_list = env_list->next;
	if (value != NULL)
	{
		new_env_list = envlist_new(key, value);
		free(key);
		key = NULL;
		free(value);
		value = NULL;
	}
	else
	{
		new_env_list = envlist_new_alone(key);
		free(key);
		key = NULL;
		free(value);
		value = NULL;
	}
	envlist_add_back(&env_list, new_env_list);
}

t_val_and_key	data_create(char *str, t_val_and_key data)
{
	int		i;

	i = 0;
	data.plus = find_plus(str);
	while (str[i] != '=' && str[i] != '+' && str[i] != '\0')
		i++;
	data.key = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=' && str[i] != '+' && str[i] != '\0')
	{
		data.key[i] = str[i];
		i++;
	}
	data.key[i] = '\0';
	if (str[i] == '+')
		i++;
	if (str[i] != '\0' && str[i])
		data.value = strdup(&str[i]);
	return (data);
}

void	add_elem_env_help_2(char *key, char *v, t_env_var *copy_e_l, int plus)
{
	if (!plus)
		change_val_ex(copy_e_l, v);
	else
		change_val_ex_plus(copy_e_l, v);
	free(key);
	key = NULL;
	free(v);
	v = NULL;
}

int	add_elem_env(char *str, t_env_var *env_list)
{
	t_env_var		*copy_e_l;
	t_val_and_key	data;

	data.value = NULL;
	data.key = NULL;
	data.plus = 0;
	if (check_argc(str))
		return (EXIT_FAILURE);
	data = data_create(str, data);
	copy_e_l = env_list;
	while (copy_e_l)
	{
		if (check_str(copy_e_l->key, data.key)
			&& ft_strlen(copy_e_l->key) == ft_strlen(data.key))
		{
			if (data.value)
				add_elem_env_help_2(data.key, data.value, copy_e_l, data.plus);
			return (EXIT_SUCCESS);
		}
		copy_e_l = copy_e_l->next;
	}	
	add_elem_env_help(env_list, data.key, data.value);
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
	update_env(env_list);
	return (EXIT_SUCCESS);
}
