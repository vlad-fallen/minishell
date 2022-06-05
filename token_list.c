/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:29:52 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/05 19:37:46 by mbutter          ###   ########.fr       */
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
		list->connect = 0;
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

void	del_elem(t_token *del, t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	free (del);
}

void	token_destroy(t_token **token)
{
	if (token != NULL)
	{
		free((*token)->value);
		(*token)->value = NULL;
		free(*token);
		*token = NULL;
	}
}

void	token_destroy_all(t_token **token)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *token;
	while (tmp != NULL)
	{
		next = tmp->next;
		token_destroy(&tmp);
		tmp = next;
	}
	*token = NULL;
}
