/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:19:47 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/10 18:15:08 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*del_elem_env(t_env_var *del, t_env_var *head)
{
	t_env_var	*tmp;

	tmp = head;
	if (head == del)
	{
		tmp = tmp->next;
		free(head->value);
		head->value = NULL;
		head->value = tmp->value;
		free(head->key);
		head->key = NULL;
		head->key = tmp->key;
		head->next = tmp->next;
		free(tmp);
		return (head);
	}
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	free(del->key);
	free(del->value);
	free (del);
	return (tmp);
}

void	del_add_elem_env(char	*str, t_env_var	*env_list)
{
	t_env_var	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (check_str(tmp->key, str))
		{
			env_list = del_elem_env(tmp, env_list);
		}
		tmp = tmp->next;
	}
}

int	unset_help(int flag_p_e, t_table_cmd *table, int i)
{
	t_env_var	*env_list;

	env_list = g_envp.env_list;
	if (flag_p_e)
	{
		print_error("minishell", "unset", table->arguments[i],
			"invalid parameter name");
		flag_p_e = 0;
	}
	else
		del_add_elem_env(table->arguments[i], env_list);
	return (flag_p_e);
}

int	ft_isalpha_and(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	unset_fun(t_table_cmd *table)
{
	int	i;
	int	exit_status;
	int	flag_print_err;
	int	j;

	exit_status = 0;
	flag_print_err = 0;
	i = 1;
	while (table->arguments[i])
	{
		j = 0;
		while (table->arguments[i][j])
		{
			if (!ft_isalpha_and(table->arguments[i][j]))
			{
				exit_status = EXIT_FAILURE;
				flag_print_err = 1;
			}
			j++;
		}
		flag_print_err = unset_help(flag_print_err, table, i);
		i++;
	}
	update_env(g_envp.env_list);
	return (exit_status);
}
