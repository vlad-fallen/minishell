/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:28:54 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/14 14:11:28 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	quote = str[0];
	while (str[len])
	{
		if (str[len] == quote)
			break ;
		len++;
	}
	if (str[len] != quote)
		return (-1);
	len++;
	return (len);
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
				del_elem(tmp_next, *list_token);
		}	
		tmp_prev = tmp_prev->next;
		tmp_next = tmp_next->next;
	}
}

/* int lexer_token_whitespace(char *input, int *i, t_token **list_token)
{
	t_token	*token;

	if (ft_isspace(input[*i]))
	{
		while (ft_isspace(input[*i]))
			(*i)++;
		token = token_new(e_white_space, " ");
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
	}
	return (0);
} */