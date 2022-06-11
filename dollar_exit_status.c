/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:34:30 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/11 16:23:42 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_len(char *value_tmp)
{
	int		count_pre;

	count_pre = 0;
	while (value_tmp[count_pre] != '$')
		count_pre++;
	return (count_pre);
}

static char	*change_exit_status_pre(int count_pre, char	*value_tmp)
{
	char	*tmp;
	char	*only_nbr;
	char	*tmp2;

	tmp = (char *)malloc(sizeof(char) * count_pre + 1);
	ft_strlcpy(tmp, value_tmp, count_pre + 1);
	only_nbr = ft_itoa(g_envp.status_exit);
	tmp2 = ft_strjoin(tmp, only_nbr);
	free(tmp);
	tmp = NULL;
	free(only_nbr);
	only_nbr = NULL;
	return (tmp2);
}

char	*change_exit_status(char *value_tmp)
{
	char	*nbr;
	char	*tmp2;
	int		count_pre;
	int		i;

	count_pre = count_len(value_tmp);
	tmp2 = change_exit_status_pre(count_pre, value_tmp);
	i = 0;
	while (i != count_pre + 2)
	{
		value_tmp++;
		i++;
	}
	nbr = ft_strjoin(tmp2, value_tmp);
	free(tmp2);
	tmp2 = NULL;
	return (nbr);
}

t_token	*dollar_exit_status_help(t_token *tmp)
{
	int		i;
	char	*value;
	char	*value_tmp;

	i = 0;
	value = tmp->value;
	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			if (value[i] == '?')
			{
				value_tmp = value;
				value = change_exit_status(value_tmp);
				free(value_tmp);
				value_tmp = NULL;
				tmp->value = value;
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
	return (dollar_pars(list_token));
}
