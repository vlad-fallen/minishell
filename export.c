/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:55:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/08 15:37:59 by echrysta         ###   ########.fr       */
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
	while (str[i] != '=' && str[i] != '\0')
		i++;
	data.key = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		data.key[i] = str[i];
		i++;
	}
	data.key[i] = '\0';
	if (str[i] != '\0' && str[i])
	{		
		data.value = strdup(&str[i]);
	}
	return (data);
}

int	add_elem_env(char *str, t_env_var *env_list)
{
	t_env_var		*copy_env_list;
	t_val_and_key	data;

	data.value = NULL;
	data.key = NULL;
	if (check_argc(str))
		return (EXIT_FAILURE);
	data = data_create(str, data);
	copy_env_list = env_list;
	while (copy_env_list)
	{
		if (check_str(copy_env_list->key, data.key)
			&& ft_strlen(copy_env_list->key) == ft_strlen(data.key))
		{
			if (data.value)
			{
				change_val_ex(copy_env_list, data.value);
				free(data.key);
				data.key = NULL;
				free(data.value);
				data.value = NULL;
			}
			return (EXIT_SUCCESS);
		}
		copy_env_list = copy_env_list->next;
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
