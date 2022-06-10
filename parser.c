/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:17:11 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/10 19:28:37 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_table_cmd	*parser(t_token **list_token)
{
	t_table_cmd	*table;
	t_table_cmd	*head;
	t_token		*next;

	table = table_create();
	if (table == NULL)
		return (NULL);
	head = table;
	while (list_token && *list_token)
	{
		if ((*list_token)->key == e_word || (*list_token)->key == e_single_quote
			|| (*list_token)->key == e_double_quote)
			add_token_to_table(list_token, &table);
		if ((*list_token) && (*list_token)->key == e_redir)
			inout_add_to_table(list_token, &table);
		if ((*list_token) && (*list_token)->key == e_pipe)
		{
			next = (*list_token)->next;
			token_destroy(list_token);
			*list_token = next;
			table->next = table_create();
			table = table->next;
		}
	}
	return (head);
}
