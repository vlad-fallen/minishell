/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:14:14 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/10 13:38:04 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *lexer_utils(t_token *list_token)
{
	t_token *tmp_prev;
	t_token *tmp_next;

	tmp_prev = list_token;
	tmp_next = list_token;
	if (tmp_next->next)
		tmp_next = tmp_next->next;
	else
		return (list_token);
	while (tmp_prev->next && tmp_next->next)
	{
		if (tmp_prev->value[0] == '-')
		{
			if (check_str(tmp_prev->value, tmp_next->value))
				del_elem(tmp_next, list_token);
		}	
		tmp_prev = tmp_prev->next;
		tmp_next = tmp_next->next;
	}
	return (list_token);
}

t_token *lexer(char *input)
{
	t_token	*list_token;
	int		i;

	i = 0;
	list_token = NULL;
	if (input[0] == 0) //без этой проверки вылетает сега
		return (list_token);	
	while (input[i])
	{
		/* if (lexer_token_whitespace(input, &i, &list_token) == 1)
			break ; */
		if (lexer_token_pipe(input, &i, &list_token) == 1)
			break ;
		if (lexer_token_bracket(input, &i, &list_token) == 1)
			break ;
		if (lexer_token_redir(input, &i, &list_token) == 1)
			break ;
		if (lexer_token_quote(input, &i, &list_token) == 1)
			break ;
		if (lexer_token_word(input, &i, &list_token) == 1)
			break ;
		while (input[i] && ft_isspace(input[i]))
			i++;
	}
	if (input[i] != '\0')
		token_destroy(list_token);
	list_token = lexer_utils(list_token);
	return (list_token);
}