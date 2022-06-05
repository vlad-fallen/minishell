/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:14:01 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/05 15:18:29 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*del_elem_list_help(t_token	*tmp, t_token *head)
{
	tmp = tmp->next;
	head->value = tmp->value;
	head->key = tmp->key;
	head->next = tmp->next;
	free(tmp);
	return (head);
}

t_token	*del_elem_list(t_token *del, t_token *head)
{
	t_token	*tmp;

	tmp = head;
	if (head == del)
	{	
		if (tmp->next)
			return (del_elem_list_help(tmp, head));
		else
		{
			free(tmp->value);
			free(tmp->next);
			free(tmp);
			return (head);
		}
	}
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	free (del);
	return (head);
}

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