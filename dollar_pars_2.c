/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:36:12 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/04 19:36:07 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*digit_arg_dol(char *value, char *old_value)
{
	char	*new_val;
	int		i;
	int		count;
	int		all_len;

	all_len = ft_strlen(old_value);
	count = all_len - correct_count(value) - 1;
	new_val = (char *)malloc(sizeof(char) * count);
	i = 0;
	while (old_value[i] != '$')
	{
		new_val[i] = old_value[i];
		i++;
	}
	new_val[i] = '\0';
	value++;
	new_val = ft_strjoin(new_val, value);
	return (new_val);
}

char	*del_posle_dol(char *old_value, char *value)
{
	char	*new_val;
	int		i;
	int		count;
	int		all_len;
	char	*ost;

	all_len = ft_strlen(old_value);
	count = all_len - correct_count(value) - 1;
	new_val = (char *)malloc(sizeof(char) * count);
	i = 0;
	while (old_value[i] != '$')
	{
		new_val[i] = old_value[i];
		i++;
	}
	new_val[i] = '\0';
	ost = value;
	i = 0;
	while (i != correct_count(value))
	{
		ost++;
		i++;
	}
	new_val = ft_strjoin(new_val, ost);
	return (new_val);
}

int	check_asc(char *change_value)
{
	int	i;
	int	flag;

	flag = 0;
	if (ft_strlen(change_value) == 1)
		return (0);
	change_value++;
	i = 0;
	while (change_value[i])
	{
		if (ft_isalpha(change_value[i]))
			flag = 1;
		i++;
	}
	if (!flag)
		return (0);
	else
		return (1);
}

int	change_value_help_count(char *old, int	c_new_val)
{
	
	while (old[c_new_val] != '$')
		c_new_val++;
	if (ft_isspace(old[c_new_val + 1]))
	{
		c_new_val++;
		c_new_val = change_value_help_count(old, c_new_val);
	}
	return (c_new_val);
}

int	change_value_help(char *old, char *env_value)
{
	int		c_new_val;
	int		i;

	c_new_val = 0;
	c_new_val = change_value_help_count(old, c_new_val);
	i = 0;
	while (env_value[i])
		i++;
	c_new_val = c_new_val + i;
	return (c_new_val);
}

char	*change_value(char *value, char *old, int len_sp_val, char *env_value)
{
	char	*new_value;
	int		c_new_val;
	int		count;
	int		i;

	// printf("old =%s\n", old);
	// printf("val =%s\n", value);
	env_value++;
	c_new_val = change_value_help(old, env_value);
	count = change_value_help_count(old, 0);
	i = 0;
	while (i++ != len_sp_val)
		value++;
	c_new_val = c_new_val + i;
	new_value = (char *)malloc(sizeof(char) * c_new_val + 1);
	i = 0;
	//printf("count = %d\n", count);	
	while (i != count)
	{
		new_value[i] = old[i];
		i++;
	}
	new_value[i] = '\0';
	new_value = ft_strjoin(new_value, env_value);
	new_value = ft_strjoin(new_value, value);
	return (new_value);
}
