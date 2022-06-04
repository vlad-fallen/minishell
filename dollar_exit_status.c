/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:34:30 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/04 21:24:32 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_exit_status(char *value_tmp)
{
	char	*nbr;
	int		count_pre;
	int		count_after;
	int		i;
	char	*only_nbr;

	count_pre = 0;
	while (value_tmp[count_pre] != '$')
		count_pre++;
	count_after = count_pre + 2;
	while (value_tmp[count_after])
		count_after++;
	nbr = (char *)malloc(sizeof(char) * count_pre + 1);
	ft_strlcpy(nbr, value_tmp, count_pre + 1);
	only_nbr = ft_itoa(g_envp.status_exit);
	nbr = ft_strjoin(nbr, only_nbr);
	i = 0;
	while (i != count_pre + 2)
	{
		value_tmp++;
		i++;
	}
	nbr = ft_strjoin(nbr, value_tmp);
	free(only_nbr);
	return (nbr);
}

t_token	*dollar_exit_status_help(t_token *tmp)
{
	int		i;
	char	*value_tmp;

	i = 0;
	value_tmp = tmp->value;
	while (value_tmp[i])
	{
		if (value_tmp[i] == '$')
		{
			i++;
			if (value_tmp[i] == '?')
			{
				value_tmp = change_exit_status(value_tmp);
				tmp->value = value_tmp;
			}
			i--;
		}
		i++;
	}
	return (tmp);
}

t_token	*dollar_exit_status(t_token *list_token)
{
	t_token	*tmp;
	char	*prev;

	prev = NULL;
	tmp = list_token;
	while (tmp)
	{
		
		if (!check_str_red(prev, "<<"))
		{
			if (tmp->key != e_single_quote)
				tmp = dollar_exit_status_help(tmp);
		}
		prev = tmp->value;
		tmp = tmp->next;
	}
	return (list_token);
}
