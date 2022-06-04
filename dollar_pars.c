/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:33:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/04 21:23:41 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str(char *str1, char *str2)
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
	return (1);
}

int	check_str_red(char *str1, char *str2)
{
	int	i;

	if (!str1)
		return (0);
	if (!str2)
		return (0);
	if (str1[0] == '\0')
		return (0);
	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	check_str_n(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && n != i)
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	correct_count(char *elem_split_value)
{
	int	i;

	i = 0;
	while (elem_split_value[i] && elem_split_value[i] != '\'' && \
		elem_split_value[i] != '$' && elem_split_value[i] != ' ' && \
		elem_split_value[i] != '\"' && elem_split_value[i] != '/' && \
		elem_split_value[i] != '=' && elem_split_value[i] != ':' )
		i++;
	return (i);
}

t_token	*dollar_pars_help(t_token *tmp, t_token *list_token)
{
	char	*change_value;

	change_value = change_in_env(tmp->value, tmp->key);
	if (change_value[0] == '\0')
		tmp = del_elem_list(tmp, list_token);
	else
		tmp->value = change_value;
	return (tmp);
}

t_token	*dollar_pars(t_token *list_token)
{
	t_token	*tmp;
	char	*prev;
	int		i;

	//print_list_token(list_token);
	prev = NULL;
	tmp = list_token;
	while (tmp)
	{
		if (!check_str_red(prev, "<<"))
		{
			i = 0;
			if (tmp->key != e_single_quote)
			{
				while (tmp->value[i])
				{
					if (tmp->value[i] == '$')
					{
						if (ft_isspace(tmp->value[i + 1]) == 0)
							tmp = dollar_pars_help(tmp, list_token);
					}
					i++;
				}
			}
		}
		prev = tmp->value;
		tmp = tmp->next;
	}
	//print_list_token(list_token);
	return (list_token);
}
