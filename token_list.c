/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:29:52 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/01 16:48:29 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(key_token key, char *value)
{
	t_token	*list;

	list = (t_token *)malloc(sizeof(t_token));
	if (list != NULL)
	{
		list->key = key;
		list->value = ft_strdup(value);
		list->next = NULL;
	}
	return (list);
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (new != NULL)
	{
		if (*lst != NULL)
		{
			tmp = *lst;
			while (tmp->next != 0)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			*lst = new;
	}
}

void	token_destroy(t_token *token)
{
	t_token *tmp;

	while (token != NULL)
	{
		tmp = token->next;
		free(token->value);
		token->value = NULL;
		free(token);
		token = tmp;
	}
}