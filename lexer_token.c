/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:26:48 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/02 16:56:13 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int token_pipe(char *input, int *i, t_token **list_token)
{
	char *token_str;
	t_token	*token;

	if (input[*i] == '|')
	{
		token_str = ft_substr(input, *i, 1);
		if (token_str == NULL)
			return (1);
		token = token_new(e_pipe, token_str);
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
		free(token_str);
		(*i)++;
	}
	return (0);
}

int token_bracket(char *input, int *i, t_token **list_token)
{
	char *token_str;
	t_token	*token;

	if (input[*i] == '(' || input[*i] == ')')
	{
		token_str = ft_substr(input, *i, 1);
		if (token_str == NULL)
			return(1);
		if (input[*i] == '(')
			token = token_new(e_left_bracket, token_str);
		else
			token = token_new(e_right_bracket, token_str);
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
		free(token_str);
		(*i)++;
	}
}

int token_redir(char *input, int *i, t_token **list_token)
{
	char *token_str;
	t_token	*token;
	int len;

	len = 0;
	/* while (ft_isdigit(input[*i + len]))
		len++; */
	if (input[*i] == '<' || input[*i] == '>')
	{
		len++;
		if (input[*i + len] == input[*i])
			len++;
		token_str = ft_substr(input, *i, len);
		if (token_str == NULL)
			return (1);
		token = token_new(e_redir, token_str);
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
		free(token_str);
		(*i) += len;
	}
	return (0);
}

int ft_quotelen(char *str)
{
	int		len;
	char	quote;

	if (str == NULL || *str == '\0')
		return (0);
	len = 0;
	if (ft_strchr("\"\'", str[len]) == NULL)
		return (0);
	len++;
	quote = str[len];
	while (str[len])
	{
		if (str[len] == quote)
			break ;
		len++;
	}
	if (str[len] != quote)
		return (-1);
	return (len);
}

int token_quote(char *input, int *i, t_token **list_token)
{
	char *token_str;
	t_token	*token;
	int len;

	len = ft_quotelen(&input[*i]);
	if (len == -1)
		return (1);
	if (len > 0)
	{
		token_str = ft_substr(input, *i + 1, len - 2);
		if (token_str == NULL)
			return (1);
		if (input[*i] == '\"')
			token = token_new(e_double_quote, token_str);
		else
			token = token_new(e_single_quote, token_str);
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
		free(token_str);
		(*i) += len;
	}
	return (0);
}

int ft_wordlen(char *str)
{
	int len;

	len = 0;
	while (str[len])
	{
		if (ft_isspace(str[len]))
			break ;
		else if (ft_strchr("()<>|\'\"", str[len]))
			break;
		len++;
	}
	return (len);
}

int token_word(char *input, int *i, t_token **list_token)
{
	char *token_str;
	t_token	*token;
	int len;

	len = ft_wordlen(&input[*i]);
	if (len == -1)
		return (1);
	if (len > 0)
	{
		token_str = ft_substr(input, *i + 1, len - 2);
		if (token_str == NULL)
			return (1);
		if (input[*i] == '\"')
			token = token_new(e_double_quote, token_str);
		else
			token = token_new(e_single_quote, token_str);
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
		free(token_str);
		(*i) += len;
	}
	return (0);
}
