/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:21:57 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/04 16:27:57 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_table_cmd *table_create(void)
{
	t_table_cmd *new_table;

	new_table = (t_table_cmd *)malloc(sizeof(t_table_cmd));
	if (new_table == NULL)
		return (NULL);
	new_table->arguments = NULL;
	new_table->redirections = NULL;
	new_table->stream_in = -1;
	new_table->stream_out = -1;
	new_table->next = NULL;
	return (new_table);
}

char *append_token_conect(t_token **list_token)
{
	char *new_str;
	char *tmp_str;
	t_token *tmp_token;

	if (!ft_strncmp((*list_token)->value, "$", 2) && (*list_token)->connect && ((*list_token)->next->key == e_double_quote 
		|| (*list_token)->next->key == e_single_quote) 
		&& !ft_strncmp((*list_token)->next->value, "", 1))
		new_str = ft_strdup("");
	else
		new_str = ft_strdup((*list_token)->value);
	while ((*list_token)->connect)
	{
		tmp_token = (*list_token)->next;
		token_destroy(*list_token);
		(*list_token) = tmp_token;
		
		tmp_str = new_str;
		new_str = ft_strjoin(tmp_str, (*list_token)->value);
		free(tmp_str);
	}
	tmp_token = (*list_token)->next;
	token_destroy(*list_token);
	(*list_token) = tmp_token;
	return (new_str);
}

char **array_join_free(char **array1, char **array2)
{
	char **new_arr;
	int i;
	int j;

	i = 0;
	j = 0;
	while (array1[i] != NULL)
		i++;
	while (array2[j] != NULL)
		j++;
	i += j;
	new_arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (new_arr == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (array1[++i] != NULL)
		new_arr[i] = ft_strdup(array1[i]);
	while (array2[++j] != NULL)
		new_arr[i++] = ft_strdup(array2[j]);
	new_arr[i] = NULL;
	arr_free(&array1);
	arr_free(&array2);
	return (new_arr);
}

void add_token_to_table(t_token **list_token, t_table_cmd **table)
{
	t_token *next;
	t_token *tmp;
	int		i;
	char	**tmp_array;

	tmp = *list_token;
	i = 0;
	while (tmp != NULL && (tmp->key == e_word || tmp->key == e_single_quote || tmp->key == e_double_quote))
	{
		i++;
		tmp = tmp->next;
	}
	tmp_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (tmp_array == NULL)
		return ;
	i = 0;
	while ((*list_token) != NULL && ((*list_token)->key == e_word || (*list_token)->key == e_single_quote || (*list_token)->key == e_double_quote))
	{
		next = (*list_token)->next;
		tmp_array[i] = append_token_conect(list_token);
		i++;
	}
	tmp_array[i] = NULL;
	if ((*table)->arguments == NULL)
		(*table)->arguments = tmp_array;
	else
		(*table)->arguments = array_join_free((*table)->arguments, tmp_array);
}

void free_table(t_table_cmd **table)
{
	t_table_cmd *tmp;
	t_table_cmd *next;
	
	tmp = *table;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		next = tmp->next;
		arr_free(&(tmp->arguments));
		free_table_redir(&(tmp->redirections));
		free(tmp);
		tmp = NULL;
		tmp = next;
	}
	*table = NULL;
}