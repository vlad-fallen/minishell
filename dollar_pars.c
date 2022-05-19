/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:33:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/14 18:39:41 by echrysta         ###   ########.fr       */
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

int	check_str_2(char *str1, char *str2, int j)
{
	int i;

	i = 0;
	j--;
	while (str1[i] != '\0' && str2[i] != '\0' && i != j)
	{
		if (str1[i] != str2[i])
			return (0); //не совпали
		i++;
	}
	return (1); //совпали
}

int	count_correct_val(char *correct_val)
{
	int	count;
	int i;

	i = 0;
	count = 0;
	while (correct_val[i] != '\0' && correct_val[i] != '$')
	{
		i++;
		count++;
	}
	return (count);
}

char	*check_dollar_elem(t_env_var	*env_init_tmp, int i, char *value)
{
	int		len_correct_val;
	int		len_env_init_tmp;
	char	*correct_val;

	correct_val = &value[i];
	correct_val++;
	while (env_init_tmp->next)
	{
		len_correct_val = count_correct_val(correct_val);
		len_env_init_tmp = ft_strlen(env_init_tmp->key);
		if (check_str_2(correct_val, env_init_tmp->key, len_correct_val) && len_correct_val == len_env_init_tmp)
		{
			return (env_init_tmp->value);
		}
		env_init_tmp = env_init_tmp->next;
	}
	return (0);
}

char	*change_dollar_token_help(char *value_of_key, char *value, int i)
{
	int		count_of_value;
	char	*new_value;
	int		j;

	count_of_value = i;
	j = 0;
	while (value_of_key[j])
	{
		count_of_value++;
		j++;
	}
	count_of_value++;
	new_value = (char *)malloc(sizeof(char) * count_of_value);
	j = 0;
	while (j != i)
	{
		new_value[j] = value[j];
		j++;
	}
	i = 1;
	while (value_of_key[i])
	{
		new_value[j] = value_of_key[i];
		j++;
		i++;
	}
	new_value[j] = '\0';
	return (new_value);
}

char	*change_dollar_token(char *value, int i)
{
	t_env_var	*env_init_tmp;
	char		*value_of_key;

	env_init_tmp = g_envp.env_list;
	value_of_key = 0;
	value_of_key = check_dollar_elem(env_init_tmp, i, value);
	if (value_of_key != 0)
		value = change_dollar_token_help(value_of_key, value, i);
	return (value);
}

t_token	*dollar_pars(t_token *list_token)
{
	t_token	*tmp;
	char	*value_tmp;
	int		i;

	tmp = list_token;
	while (tmp)
	{
		i = 0;
		value_tmp = tmp->value;
		while(value_tmp[i])
		{
			if (value_tmp[i] == '$')
			{
				printf("lol\n");
				value_tmp = change_dollar_token(value_tmp, i);
				tmp->value = value_tmp;
			}
			i++;
		}
		tmp = tmp->next;
	}
	return(list_token);
}