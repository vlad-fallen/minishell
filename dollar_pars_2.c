/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:36:12 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/10 20:08:24 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_value_help_count(char *old, int c_new_val)
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

static int	change_value_help(char *old, char *env_value)
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

static char	*ch_val_help_2(char *old, char *env_val, int c_n_val, char *value)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*new_value;
	int		count;

	count = change_value_help_count(old, 0);
	tmp = (char *)malloc(sizeof(char) * c_n_val + 1);
	i = 0;
	while (i != count)
	{
		tmp[i] = old[i];
		i++;
	}
	tmp[i] = '\0';
	tmp2 = ft_strjoin(tmp, env_val);
	free(tmp);
	tmp = NULL;
	new_value = ft_strjoin(tmp2, value);
	free(tmp2);
	tmp2 = NULL;
	return (new_value);
}

char	*change_value(char *value, char *old, int len_sp_val, char *env_value)
{
	char	*new_value;
	int		c_new_val;
	int		i;

	env_value++;
	c_new_val = change_value_help(old, env_value);
	i = 0;
	while (i++ != len_sp_val)
		value++;
	c_new_val = c_new_val + i;
	new_value = ch_val_help_2(old, env_value, c_new_val, value);
	return (new_value);
}

char	*digit_arg_dol(char *value, char *old_value)
{
	char	*new_val;
	char	*tmp;
	int		i;
	int		count;
	int		all_len;

	all_len = ft_strlen(old_value);
	count = all_len - correct_count(value) - 1;
	tmp = (char *)malloc(sizeof(char) * count);
	i = 0;
	while (old_value[i] != '$')
	{
		tmp[i] = old_value[i];
		i++;
	}
	tmp[i] = '\0';
	value++;
	new_val = ft_strjoin(tmp, value);
	free(tmp);
	tmp = NULL;
	return (new_val);
}
