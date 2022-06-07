/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:33:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/07 20:13:44 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*change_in_env_help(char *value, int flag_ex)
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

int	check_str_for_clean(char *str1, char *str2)
{
	int	i;

	if (!str1)
		return (0);
	if (!str2)
		return (0);
	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	return (1);
}

int	count_token(t_token *list_token)
{
	int	i;

	i = 0;
	while (list_token)
	{
		list_token = list_token->next;
		i++;
	}
	return (i);
}

static t_token	*dollar_pars_help(t_token *tmp, t_token *list_token, int i)
{
	char	*change_value;

	if (ft_isspace(tmp->value[i + 1]) == 0)
	{
		change_value = change_in_env(tmp->value, tmp->key);
		//printf("change_value = %s\n", change_value);
		//printf("tmp->value = %s\n", tmp->value);
		//printf("check_str_for_clean(change_value, tmp->value) = %d\n", check_str_for_clean(change_value, tmp->value));
		if (!check_str_for_clean(change_value, tmp->value))
		{
			free(tmp->value);
			tmp->value = NULL;
		}
	//	printf("change_value = %s, p = %p\n", change_value, &change_value);
		//printf("tmp->value = %s, p = %p\n", tmp->value, &tmp->value);
		if (!change_value)
		{
			tmp = del_elem_list(tmp, &list_token);
		}
		else
		{
			//printf("ya tut\n");
			//printf("change_value = %s\n", change_value);
			tmp->value = change_value;
		}
	}
	return (tmp);
}

t_token	*dollar_pars(t_token *list_token)
{
	t_token	*tmp;
	t_token **head;
	char	*prev;
	int		i;

	prev = NULL;
	tmp = list_token;
	head = &tmp;
	while (tmp)
	{
		if (!check_str_red(prev, "<<"))
		{
			i = 0;
			if (tmp->key != e_single_quote)
			{
				while (tmp && tmp->value[i])
				{
					if (tmp->value[i] == '$')
					{
						tmp = dollar_pars_help(tmp, list_token, i);
						if (tmp && ft_isalpha(tmp->value[i + 1]))
							i = -1;
					}
					i++;
				}
			}
		}
		if (tmp != NULL)
		{	
			prev = tmp->value;
			tmp = tmp->next;
		}
	}
	// printf("count_token(list_token) = %d\n", count_token(list_token));
	if (count_token(list_token) == 1 && !list_token->next && !list_token->value)
		list_token = NULL;
	// printf("p list token = %p\n", list_token);
	// printf("p tmp = %p\n", tmp);
	// printf("p tmp next = %p\n", tmp);
	// printf("p tmp value = %p\n", tmp);
	//token_destroy_all(&list_token);
	//return (*head);
	return(list_token);
}
