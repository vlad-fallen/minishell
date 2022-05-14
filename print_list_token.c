/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:33:46 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/14 19:13:38 by mbutter          ###   ########.fr       */
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
		printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}