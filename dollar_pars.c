/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:33:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/19 15:58:23 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0); //не совпали
		i++;
	}
	return (1); //совпали
}

int	check_str_n(char *str1, char *str2, int n)
{
	int i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && n != i)
	{
		if (str1[i] != str2[i])
			return (0); //не совпали
		i++;
	}
	return (1); //совпали
}

t_token	*del_elem_list(t_token *del, t_token *head)
{
	t_token	*tmp;

	tmp = head;
	if (head == del)
	{
		tmp = tmp->next;
		head->value = tmp->value;
		head->key = tmp->key;
		head->next = tmp->next;
		free(tmp);
		return (head);
	}
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	free (del);
	return (tmp);
}

int	correct_count(char *elem_split_value)
{
	int i;

	i = 0;
	while (elem_split_value[i] && elem_split_value[i] != '\'' && elem_split_value[i] != '$' && elem_split_value[i] != ' ' && elem_split_value[i] != '\"' && elem_split_value[i] != '/')
	{
		i++;
	}
	return (i);
}

char	*change_value(char *value, char *old_value, int len_sp_val, char *env_value)
{
	char	*new_value;
	int		c_new_val;
	int		i;

	env_value++;
	c_new_val = 0;
	while (old_value[c_new_val] != '$')
	{
		c_new_val++;
	}
	i = 0;
	while (env_value[i])
	{
		i++;
	}
	c_new_val = c_new_val + i;
	i = 0;
	while (i != len_sp_val)
	{
		//printf("loo\n");
		value++;
		i++;
	}
	c_new_val = c_new_val + i;
	new_value = (char *)malloc(sizeof(char) * c_new_val + 1);
	i = 0;
	while (old_value[i] != '$')
	{
		new_value[i] = old_value[i];
		i++;
	}
	new_value[i] = '\0';
	new_value = ft_strjoin(new_value, env_value);
	new_value = ft_strjoin(new_value, value);
	// printf("NEW VAL = %s\n", new_value);
	// printf("c_new_val = %d\n", c_new_val);
	return (new_value);
}

char	*change_in_env(char *value)
{
	int			i;
	char		*old_value;
	t_env_var	*env;
	int			len_env;
	int			len_sp_val;
	int			yes_flag;
	char		*new_value;

	i = 0;
	yes_flag = 0;
	old_value = value;
	if (value[0] == '\"')
		return(old_value);
	//printf("value = %s\n", value);
	while (value[0] != '$')
	{
		value++;
		i++;
	}
	value++;
	//printf("value++ = %s\n", value);
	env = g_envp.env_list;
	while (env)
	{
		len_env = ft_strlen(env->key);
		len_sp_val = correct_count(value);
		// printf("len_env = %d\n", len_env);
		// printf("len_sp_val = %d\n", len_sp_val);
		if (check_str_n(env->key, value, len_sp_val) && len_env == len_sp_val)
		{
			new_value = change_value(value, old_value, len_sp_val, env->value);
			yes_flag = 1;
		}
	env = env->next;
	}
	if (yes_flag == 1)
		return (new_value);
	else
		return (old_value);
}

int	check_asc(char *change_value)
{
	int	i;
	int	flag;

	flag = 0;
	if (ft_strlen(change_value) == 1)
		return (0); // не удалять
	change_value++;
	i = 0;
	while (change_value[i])
	{
		//printf("%c - %d\n", change_value[i], ft_isalpha(change_value[i]));
		if (ft_isalpha(change_value[i]))
			flag = 1;
		i++;
	}
	if (!flag)
		return (0);
	else
		return (1);
}

t_token	*dollar_pars(t_token *list_token)
{
	t_token	*tmp;
	char	*change_value;
	int		i;

	//print_list_token(list_token);
	tmp = list_token;
	while (tmp)
	{
		i = 0;
		while (tmp->value[i])
		{
			if (tmp->value[i] == '$')
			{
				change_value = change_in_env(tmp->value);
				if (check_str(change_value, tmp->value) && change_value[0] != '\"' && check_asc(change_value))
				{
					// printf("NUZNO UDALIT\n");
					// printf("change_value %s\n", change_value);
					tmp = del_elem_list(tmp, tmp);
				}
				else
				{
					tmp->value = change_value;
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
	return(list_token);
}