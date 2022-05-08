/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:17:11 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/08 18:21:40 by mbutter          ###   ########.fr       */
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
	t_token *tmp;
	int		i;

	tmp = *list_token;
	i = 0;
	while (tmp != NULL && (tmp->key == e_word || tmp->key == e_single_quote || tmp->key == e_double_quote))
	{
		i++;
		tmp = tmp->next;
	}
	(*cmd)->arguments = (char **)malloc(sizeof(char *) * (i + 1));
	if ((*cmd)->arguments == NULL)
		return ;
	i = 0;
	while ((*list_token) != NULL && ((*list_token)->key == e_word || (*list_token)->key == e_single_quote || (*list_token)->key == e_double_quote))
	{
		next = (*list_token)->next;
		/* (*list_token)->next = NULL;
		token_add_back(&((*cmd)->arguments), *list_token); */
		(*cmd)->arguments[i] = ft_strdup((*list_token)->value);
		token_destroy(*list_token);
		i++;
		(*list_token) = next;
	}
	(*cmd)->arguments[i] = NULL;
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

t_token *create_redir_file_token(t_token **list_token)
{
	t_token *tmp_token;
	t_token *redir_file;
	char	*tmp_str;

	redir_file = token_new(e_redir_file, "");
	tmp_token = (*list_token)->next;
	token_destroy((*list_token));
	(*list_token) = tmp_token;
	while ((*list_token)->connect)
	{
		tmp_str = redir_file->value;
		tmp_token = (*list_token)->next;
		redir_file->value = ft_strjoin(tmp_str, (*list_token)->value);
		token_destroy(*list_token);
		(*list_token) = tmp_token;
	}
	return (redir_file);
}

void inout_add_to_table(t_token **list_token, t_table_cmd **table)
{
	t_token *redir_file;

	if ((*list_token)->key == e_redir && !ft_strncmp((*list_token)->value, ">", 2))
	{
		redir_file = create_redir_file_token(list_token);
		token_add_back(&((*table)->out), redir_file);
	}
	else if ((*list_token)->key == e_redir && !ft_strncmp((*list_token)->value, ">>", 3))
	{
		redir_file = create_redir_file_token(list_token);
		token_add_back(&((*table)->out_append), redir_file);
	}
	else if ((*list_token)->key == e_redir && !ft_strncmp((*list_token)->value, "<", 2))
	{
		redir_file = create_redir_file_token(list_token);
		token_add_back(&((*table)->in), redir_file);
	}
	else if ((*list_token)->key == e_redir && !ft_strncmp((*list_token)->value, "<<", 3))
	{
		// heredoc
	}
}

t_table_cmd *parser(t_token *list_token)
{
	t_table_cmd	*table;
	t_cmd_arg	*cmd;
	t_token		*tmp;
	
	table = (t_table_cmd *)malloc(sizeof(t_table_cmd));
	table->commands = NULL;
	table->in = NULL;
	table->out = NULL;
	while (list_token)
	{
		cmd = cmd_create();
		if (list_token->key == e_word || list_token->key == e_single_quote || list_token->key == e_double_quote)
		{
			add_token_to_cmd(&list_token, &cmd);
			cmd_add_back(&(table->commands), cmd);
			//printf("1\n");
		}
		else if (list_token->key == e_redir)
		{
			inout_add_to_table(&list_token, &table);
		}
		else
		{
			// delete pipe token and bracket token
			tmp = list_token->next;
			token_destroy(list_token);
			list_token = tmp;
		}
		//list_token = list_token->next;
	}
	return (table);
}
