/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:27:17 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/04 20:41:05 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redir_add_back(t_table_cmd **table, t_redir *new_redir)
{
	t_redir	*tmp;

	if (new_redir != NULL)
	{
		if ((*table)->redirections != NULL)
		{
			tmp = (*table)->redirections;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = new_redir;
		}
		else
			(*table)->redirections = new_redir;
	}
}

int find_redir_type(t_token *list_token)
{
	if (!ft_strncmp(list_token->value, ">", 2))
		return (REDIR_OUT);
	else if (!ft_strncmp(list_token->value, "<", 2))
		return (REDIR_IN);
	else if (!ft_strncmp(list_token->value, ">>", 3))
		return (REDIR_APPEND);
	else if (!ft_strncmp(list_token->value, "<<", 3))
		return (REDIR_HEREDOC);
	return (0);
}

t_redir *create_redir(t_token **list_token, int redir_type)
{
	t_redir *redirections;
	t_token *tmp_token;
	/* int		quote_flag;
	char	*tmp; */

	redirections = (t_redir *)malloc(sizeof(t_redir));
	if (redirections == NULL)
		return (NULL);
	//quote_flag = 0;
	redirections->type = redir_type;
	tmp_token = (*list_token)->next;
	token_destroy((*list_token));
	(*list_token) = tmp_token;
	/* if ((*list_token)->key == e_single_quote)
		quote_flag = 1;
	else if ((*list_token)->key == e_double_quote)
		quote_flag = 2; */
	redirections->name = append_token_conect(list_token);
	/* if (redirections->type == REDIR_HEREDOC && quote_flag > 0)
	{
		tmp = redirections->name;
		redirections->name = ft_strjoin("\"", tmp);
		free(tmp);
	} */
	return (redirections);
}

void inout_add_to_table(t_token **list_token, t_table_cmd **table)
{
	t_redir *redir_file;

	while ((*list_token) && (*list_token)->key == e_redir)
	{
		redir_file = create_redir(list_token, find_redir_type(*list_token));
		redir_add_back(table, redir_file);
	}
}
void	free_table_redir(t_redir **redir)
{
	t_redir *tmp;
	t_redir *next;
	
	tmp = *redir;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name);
		tmp->name = NULL;
		free(tmp);
		tmp = NULL;
		tmp = next;
	}
	*redir = NULL;
}