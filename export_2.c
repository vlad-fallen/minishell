/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:47:04 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/08 16:03:10 by echrysta         ###   ########.fr       */
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
