/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:06:19 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/08 22:09:17 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
