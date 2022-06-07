/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:58:29 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/07 15:00:57 by echrysta         ###   ########.fr       */
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

char	*correct_dollar_pos(char *value)
{
	int	i;

	i = 0;
	while (value[0] != '$' && value)
	{
		value++;
		i++;
	}
	value++;
	if (ft_isspace(value[0]))
	{
		value = correct_dollar_pos(value);
	}
	return (value);
}
