/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:33:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/06 21:39:24 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_token	*dollar_pars_help(t_token *tmp, t_token *list_token, int i)
{
	char	*change_value;

	if (ft_isspace(tmp->value[i + 1]) == 0)
	{
		//printf("do = %s\n", tmp->value);
		change_value = change_in_env(tmp->value, tmp->key);
		//printf("posle = %s\n", change_value);
		if (change_value[0] == '\0')
			tmp = del_elem_list(tmp, &list_token);
		else
			tmp->value = change_value;
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
	//token_destroy_all(&list_token);
	return (*head);
}
