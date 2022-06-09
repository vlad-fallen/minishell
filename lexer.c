/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:14:14 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/08 20:48:57 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int syntax_error(t_token *list_token)
{
	if (list_token->key == e_pipe && list_token->next == NULL)
		return (print_error("minishell", "syntax error", NULL,
				"incomplete pipe"));
	if (list_token->key == e_pipe && list_token->next->key == e_pipe)
		return (print_error("minishell", "syntax error", NULL,
				"incomplete pipe"));
	if (list_token->key == e_redir && list_token->next == NULL)
		return (print_error("minishell", "syntax error", NULL,
				"invalid redirection"));
	if (list_token->key == e_redir && list_token->next->key == e_redir)
		return (print_error("minishell", "syntax error", NULL,
				"invalid redirection"));
	if (list_token->key == e_redir && list_token->next->key == e_pipe)
		return (print_error("minishell", "syntax error", NULL,
				"invalid redirection"));
	return (0);
}

static int	check_syntax(t_token *list_token)
{
	int empty_flag;
	int err_flag;

	empty_flag = 1;
	err_flag = 0;
	if (list_token && list_token->key == e_pipe)
		return (-1);
	while (list_token)
	{
		if (syntax_error(list_token))
		{
			err_flag = 1;
			break ;
		}
		/* if (list_token->key == e_pipe && list_token->next == NULL)
		return (print_error("minishell", "syntax error", NULL,
				"incomplete pipe"));
		if (list_token->key == e_pipe && list_token->next->key == e_pipe)
			return (print_error("minishell", "syntax error", NULL,
					"incomplete pipe"));
		if (list_token->key == e_redir && list_token->next == NULL)
			return (print_error("minishell", "syntax error", NULL,
					"invalid redirection"));
		if (list_token->key == e_redir && list_token->next->key == e_redir)
			return (print_error("minishell", "syntax error", NULL,
					"invalid redirection"));
		if (list_token->key == e_redir && list_token->next->key == e_pipe)
			return (print_error("minishell", "syntax error", NULL,
					"invalid redirection")); */
		/* if (ft_strncmp(list_token->value, "\0", 1) && empty_flag == 1)
			empty_flag = 0; */
		list_token = list_token->next;
	}
	/* if (empty_flag == 1)
		return (1); */
	/* if (empty_flag == 1)
	{
		err_flag = 1;
		g_envp.status_exit = 127;
	}
	else
		g_envp.status_exit = 2; */
	return (err_flag);
}

t_token	*lexer(char *input)
{
	t_token	*list_token;
	int		i;

	i = 0;
	list_token = NULL;
	if (input[0] == 0)
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
	return (list_token);
}
