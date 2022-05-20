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

char	*change_split_val(char *env_val)
{
	char	*new_val;

	env_val++;
	new_val = ft_strdup(env_val);
	return (new_val);
}

char	*creat_new_val(char **split_value)
{
	char	*new_val;
	int		all_len;
	int		i;
	int		j;

	printf("split\n");
	print_list_arguments(split_value);
	i = 0;
	all_len = 0;
	while (split_value[i])
	{
		all_len = all_len + ft_strlen(split_value[i]);
		i++;
	}
	i = 0;
	all_len = 0;
	new_val = (char *)malloc(sizeof(char) * all_len + 1);
	while (split_value[i])
	{
		j = 0;
		while (split_value[i][j])
		{
			new_val[all_len] = split_value[i][j];
			j++;
			all_len++;
		}
		i++;
	}
	new_val[all_len] = '\0';
	printf("new_va = %s\n", new_val);
	return (new_val);
}

char	*change_in_env(char **split_value)
{
	int			i;
	t_env_var	*env;
	int			len_env;
	int			len_sp_val;
	char		*new_value_tmp;

	i = 0;
	while (split_value[i])
	{
		env = g_envp.env_list;
		while (env)
		{
			len_env = ft_strlen(env->key);
			len_sp_val = ft_strlen(split_value[i]);
			if (check_str(env->key, split_value[i]) && len_env == len_sp_val)
			{
				split_value[i] = change_split_val(env->value);
			}
			env = env->next;
		}
		i++;
	}
	new_value_tmp = creat_new_val(split_value);
	return (new_value_tmp);
}

t_token	*dollar_pars(t_token *list_token)
{
	t_token	*tmp;
	char	**split_value;

	tmp = list_token;
	while (tmp)
	{
		split_value = ft_split(tmp->value, '$');
		tmp->value = change_in_env(split_value);
		free(split_value);
		tmp = tmp->next;
	}
	print_list_token(list_token);
	return(list_token);
}