/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:58:29 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/04 16:53:36 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*del_elem_list_help(t_token	*tmp, t_token *head)
{
	tmp = tmp->next;
	head->value = tmp->value;
	head->key = tmp->key;
	head->next = tmp->next;
	free(tmp);
	return (head);
}

t_token	*del_elem_list(t_token *del, t_token *head)
{
	t_token	*tmp;

	tmp = head;
	if (head == del)
	{	
		
		if (tmp->next)
			return (del_elem_list_help(tmp, head));
		else
		{
			free(tmp->value);
			free(tmp->next);
			free(tmp);
			return (head);
		}
	}
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	free (del);
	return (head);
}

char	*change_in_env_help(char *value)
{
	int	i;

	i = 0;
	while (value[0] != '$')
	{
		value++;
		i++;
	}
	value++;
	return (value);
}

char	*change_in_env(char *value, int flag_ex)
{
	char		*old_value;
	t_env_var	*env;
	int			len_env;
	int			len_sp_val;
	//char		*tmp;

	env = g_envp.env_list;
	old_value = value;
	if (value[0] == '\"')
		return (old_value);
	if (flag_ex == 3)
	{
		// value = change_in_env_help(value);
		//value = correct_dollar_pos(value)
	}
	value = change_in_env_help(value);
	if (ft_isdigit(value[0]))
		return (digit_arg_dol(value, old_value));
	//printf("value =%s\n", value);
	//printf("oldvalue =%s\n", old_value);
	while (env)
	{
		len_env = ft_strlen(env->key);
		len_sp_val = correct_count(value);
		if (check_str_n(env->key, value, len_sp_val) && len_env == len_sp_val)
			return (change_value(value, old_value, len_sp_val, env->value));
		env = env->next;
	}
	if (ft_isalpha(value[0]))
		return (del_posle_dol(old_value, value));
	return (old_value);
}
