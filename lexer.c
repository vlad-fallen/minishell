/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:14:14 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/10 16:53:12 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void find_duplicate_flags(t_token **list_token)
{
	t_token *tmp_prev;
	t_token *tmp_next;

	if (!(*list_token) && !(*list_token)->next)
		return ;
	tmp_prev = *list_token;
	tmp_next = (*list_token)->next;
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
	find_duplicate_flags(&list_token);
	return (list_token);
}