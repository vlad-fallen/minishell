/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:17:11 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/03 18:05:06 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_arg *cmd_create(void)
{
	t_cmd_arg *new_cmd;

	new_cmd = (t_cmd_arg *)malloc(sizeof(t_cmd_arg));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->arguments = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void add_token_to_cmd(t_token **list_token, t_cmd_arg **cmd)
{
	t_token *next;
	
	while ((*list_token) != NULL && ((*list_token)->key == e_word || (*list_token)->key == e_single_quote || (*list_token)->key == e_double_quote))
	{
		next = (*list_token)->next;
		(*list_token)->next = NULL;
		token_add_back(&((*cmd)->arguments), *list_token);
		(*list_token) = next;
	}
}

void cmd_add_back(t_cmd_arg **list_cmd, t_cmd_arg *new_cmd)
{
	t_cmd_arg	*tmp;

	if (new_cmd != NULL)
	{
		if (*list_cmd != NULL)
		{
			tmp = *list_cmd;
			while (tmp->next != 0)
				tmp = tmp->next;
			tmp->next = new_cmd;
		}
		else
			*list_cmd = new_cmd;
	}
}

t_table_cmd *parser(t_token *list_token)
{
	t_table_cmd	*table;
	t_cmd_arg	*cmd;
	
	table = (t_table_cmd *)malloc(sizeof(t_table_cmd));
	table->commands = NULL;
	table->in = NULL;
	table->out = NULL;
	while (list_token)
	{
		cmd = cmd_create();
		if (list_token->key == e_word || list_token->key == e_single_quote || list_token->key == e_double_quote)
			add_token_to_cmd(&list_token, &cmd);
		cmd_add_back(&(table->commands), cmd);
		//list_token = list_token->next;
	}
	return (table);
}
