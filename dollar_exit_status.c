/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:34:30 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/14 17:22:23 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_exit_status(char *value_tmp)
{
	char	*nbr;
	
	free(value_tmp);
	nbr = (char *)malloc(sizeof(char) * 4);
	nbr = ft_itoa(g_envp.status_exit);
	return (nbr);
}

t_token	*dollar_exit_status(t_token *list_token)
{
	t_token	*tmp;
	char	*value_tmp;
	int		i;
	int		j;

	tmp = list_token;
	while (tmp)
	{
		i = 0;
		value_tmp = tmp->value;
		while(value_tmp[i])
		{
			if (value_tmp[i] == '$')
			{
				j = i;
				j++;
				if (value_tmp[j] == '?')
					value_tmp = change_exit_status(value_tmp);
				tmp->value = value_tmp;
			}
			i++;
		}
		tmp = tmp->next;
	}
	return(list_token);
}