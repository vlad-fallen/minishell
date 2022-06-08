/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:47:04 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/08 15:29:31 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_help(t_env_var	*copy_list, int i)
{
	char	*tmp;
	char	*tmp2;
	char	**new_env;

	arr_free(&g_envp.env);
	g_envp.env = NULL;
	new_env = (char **)malloc((i + 2) * sizeof(char *));
	i = 0;
	while (copy_list)
	{
		tmp = ft_strdup(copy_list->key);
		if (copy_list->value)
		{
			tmp2 = ft_strdup(copy_list->value);
			new_env[i] = ft_strjoin(tmp, tmp2);
			free(tmp);
			free(tmp2);
		}
		else
			new_env[i] = tmp;
		tmp = NULL;
		tmp2 = NULL;
		copy_list = copy_list->next;
		i++;
	}
	new_env[i] = NULL;
	g_envp.env = new_env;
}

void	update_env(t_env_var *env_list)
{
	t_env_var	*copy_list;

	int			i;

	i = 0;
	copy_list = env_list;
	while (copy_list)
	{
		copy_list = copy_list->next;
		i++;
	}
	copy_list = env_list;
	update_env_help(copy_list, i);
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
	char	ch;
	int		i;

	i = 1;
	ch = str[0];
	if (!(97 <= ch && ch <= 122) && !(65 <= ch && ch <= 90))
	{
		print_error("minishell", "export", str, "not a valid identifier");
		return (EXIT_FAILURE);
	}
	while (str[i] != '=' && str[i])
	{
		ch = str[i];
		if (!(97 <= ch && ch <= 122) && !(65 <= ch && ch <= 90)
			&& !(48 <= ch && ch <= 57))
		{
			print_error("minishell", "export", str, "not a valid identifier");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	change_val_ex(t_env_var	*list, char *val)
{
	char	*new_val;

	if (ft_strlen(val) == 1)
	{
		free(list->value);
		list->value = NULL;
		new_val = (char *)malloc(sizeof(char) * 1);
		new_val[0] = '\0';
		list->value = strdup(new_val);
		free(new_val);
		new_val = NULL;
		return ;
	}
	else
	{
		free(list->value);
		list->value = NULL;
		list->value = ft_strdup(val);
		return ;
	}
}
