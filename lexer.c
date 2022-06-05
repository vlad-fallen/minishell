/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:14:14 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/05 17:18:45 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_syntax(t_token *list_token)
{
	if (list_token && list_token->key == e_pipe)
		return (-1);
	while (list_token)
	{
		//error with pipe
		if (list_token->key == e_pipe && list_token->next == NULL)
			return (print_error("minishell", "syntax error", NULL, "incomplete pipe"));
		if (list_token->key == e_pipe && list_token->next->key == e_pipe)
			return (print_error("minishell", "syntax error", NULL, "incomplete pipe"));
		//error with redirection
		if (list_token->key == e_redir && list_token->next == NULL)
			return (print_error("minishell", "syntax error", NULL, "invalid redirection"));
		if (list_token->key == e_redir && list_token->next->key == e_redir)
			return (print_error("minishell", "syntax error", NULL, "invalid redirection"));
		if (list_token->key == e_redir && list_token->next->key == e_pipe)
			return (print_error("minishell", "syntax error", NULL, "invalid redirection"));
		list_token = list_token->next;
	}
	return (0);
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
	list_token = dollar_exit_status(list_token);
	list_token = dollar_pars(list_token);
	list_token = expand_prog(list_token);
	if (input[i] != '\0' || check_syntax(list_token))
	{
		token_destroy_all(&list_token);
		g_envp.status_exit = 2;
	}
	//print_list_token(list_token);
	return (list_token);
}