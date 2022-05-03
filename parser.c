/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:17:11 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/03 15:50:03 by mbutter          ###   ########.fr       */
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

void add_token_to_cmd(t_token **list_token, )
{
	
}

t_table_cmd *parser(t_token *list_token)
{
	t_table_cmd	*table;
	t_cmd_arg	*cmd;
	
	while (list_token)
	{
		if (list_token->key == )
		list_token = list_token->next;
	}
}