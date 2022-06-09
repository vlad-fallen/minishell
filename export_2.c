/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:47:04 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/09 18:54:09 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while ((str[i] != '=' && str[i]) || (str[i] != '='
			&& str[i - 1] != '+' && str[i]))
	{
		ch = str[i];
		if (!(97 <= ch && ch <= 122) && !(65 <= ch && ch <= 90)
			&& !(48 <= ch && ch <= 57) && !(str[i + 1] == '=' && str[i] == '+'))
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
		list->value = ft_strdup(new_val);
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

void	change_val_ex_plus(t_env_var	*list, char *val)
{
	char	*new_val;

	val++;
	new_val = ft_strjoin(list->value, val);
	free(list->value);
	list->value = NULL;
	list->value = new_val;
}

int	find_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}
