/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:58:29 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/05 20:15:48 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*correct_dollar_pos(char *value)
{
	int	i;

	i = 0;
	while (value[0] != '$' && value)
	{
		value++;
		i++;
	}
	value++;
	if (ft_isspace(value[0]))
	{
		value = correct_dollar_pos(value);
	}
	return (value);
}

char	*change_in_env_help(char *value, int flag_ex)
{
	int	i;

	if (flag_ex == e_double_quote)
		value = correct_dollar_pos(value);
	else
	{
		i = 0;
		while (value[0] != '$')
		{
			value++;
			i++;
		}
		value++;
	}
	return (value);
}

char	*change_in_env(char *value, int flag_ex)
{
	char		*old_value;
	t_env_var	*env;
	int			len_env;
	int			len_sp_val;

	//printf("value = %s\n", value);
	env = g_envp.env_list;
	old_value = value;
	if (value[0] == '\"')
		return (old_value);
	value = change_in_env_help(value, flag_ex);
	if (ft_isdigit(value[0]))
		return (digit_arg_dol(value, old_value));
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
