/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:33:46 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/03 17:33:47 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_token(t_token *list_token)
{
	t_token *tmp;

	tmp = list_token;
	while (tmp)
	{
		printf("list_token->next %s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	print_list_env(t_env_var *list_token)
{
	t_env_var *tmp;

	tmp = list_token;
	while (tmp)
	{
		printf("tmp->key %s\n", tmp->key);
		printf("tmp->value %s\n", tmp->value);
		tmp = tmp->next;
	}
}