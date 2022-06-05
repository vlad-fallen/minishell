/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:33:46 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/05 17:33:16 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_token(t_token *list_token)
{
	t_token	*tmp;

	tmp = list_token;
	while (tmp)
	{
		printf("list_token->next %s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	print_list_arguments(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("arg[i] = %s\n", arg[i]);
		i++;
	}
}

void	print_list_env(t_env_var *list_token)
{
	t_env_var	*tmp;

	tmp = list_token;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
}
