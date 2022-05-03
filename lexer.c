/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:14:14 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/03 16:23:47 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_token *lexer(char *input)
{
	t_token	*list_token;
	int		i;

	i = 0;
	list_token = NULL;
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
	return (list_token);
}