/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:14:01 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/08 22:03:58 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*del_elem_list(t_token *del, t_token **head)
{
	t_token	*prev;
	t_token	*tmp;

	prev = *head;
	tmp = *head;
	while (tmp != del)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev == tmp)
		token_destroy(head);
	else
	{
		prev->next = tmp->next;
		token_destroy(&tmp);
	}
	return (*head);
}

static char	*del_posle_dol_help(char *old_value, char *value)
{
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
	return (tmp);
}

char	*del_posle_dol(char *old_value, char *value)
{
	char	*new_val;
	char	*tmp;
	char	*ost;
	int		i;

	tmp = del_posle_dol_help(old_value, value);
	ost = value;
	i = 0;
	while (i != correct_count(value))
	{
		ost++;
		i++;
	}
	new_val = ft_strjoin(tmp, ost);
	free(tmp);
	tmp = NULL;
	if (new_val[0] == '\0')
	{
		free(new_val);
		new_val = NULL;
	}
	return (new_val);
}
