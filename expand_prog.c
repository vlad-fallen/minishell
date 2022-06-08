/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:44:51 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/08 21:12:17 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_token	*expand_prog(t_token *list_token)
{
	t_token	*tmp;
	char	*prev;

	if (!list_token)
		return (list_token);
	prev = NULL;
	tmp = list_token;
	while (tmp)
	{
		if (!check_str_red(prev, "<<"))
		{
			if (find_dollar(tmp->value))
			{
				if (tmp->key != e_single_quote
					&& tmp->key != e_double_quote && tmp->connect == 1)
				{
					list_token = del_elem_list(tmp, &list_token);
					tmp = list_token;
				}
			}
		}
		prev = tmp->value;
		tmp = tmp->next;
	}
	return (list_token);
}
