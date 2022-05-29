/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:44:51 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/29 15:06:22 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_dollar(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1); //нашел доллар
		i++;
	}
	return (0);
}

t_token	*expand_prog(t_token *list_token)
{
	t_token	*tmp;
	
	//print_list_token(list_token);
	tmp = list_token;
	while (tmp)
	{
		if (find_dollar(tmp->value))
			if (tmp->key != e_single_quote && tmp->key != e_double_quote && tmp->connect == 1)
			{
				//printf("del token\n");
				del_elem_list(tmp, list_token);
			}
		tmp = tmp->next;
	}
	//print_list_token(list_token);
	return (list_token);
}
