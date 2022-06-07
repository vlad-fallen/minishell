/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:14:14 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/07 20:13:17 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_token *list_token)
{
	int empty_flag;

	empty_flag = 1;
	if (list_token && list_token->key == e_pipe)
		return (-1);
	while (list_token)
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
		if (ft_strncmp(list_token->value, "\0", 1) && empty_flag == 1)
			empty_flag = 0;
		list_token = list_token->next;
	}
	if (empty_flag == 1)
		return (1);
	return (0);
}

t_token	*lexer(char *input)
{
	t_token	*list_token;
	//t_token *tmp;
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
	//tmp = list_token;
	list_token = dollar_exit_status(list_token);
	//token_destroy_all(&tmp);
	//tmp = list_token;
	list_token = dollar_pars(list_token);
	//token_destroy_all(&tmp);
	//tmp = list_token;
	list_token = expand_prog(list_token);
	//token_destroy_all(&tmp);
	if (input[i] != '\0' || check_syntax(list_token))
	{
		token_destroy_all(&list_token);
		g_envp.status_exit = 2;
	}
	return (list_token);
}
