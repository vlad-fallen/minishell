/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:29:52 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/10 12:10:22 by echrysta         ###   ########.fr       */
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

//дописал удаление токена из середины списка ил конца
void	del_elem(t_token *del, t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	free (del);
}

void	token_destroy(t_token *token)
{
	if (token != NULL)
	{
		free(token->value);
		token->value = NULL;
		free(token);
	}
}

/* void	token_destroy(t_token *token)
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
} */