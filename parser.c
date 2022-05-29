/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:17:11 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/21 20:03:50 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*-------UTILS--------*/

t_table_cmd *table_create(void)
{
	t_table_cmd *new_table;

	new_table = (t_table_cmd *)malloc(sizeof(t_table_cmd));
	if (new_table == NULL)
		return (NULL);
	new_table->arguments = NULL;
	new_table->redirections = NULL;
	new_table->next = NULL;
	return (new_table);
}

/*-------UTILS--------*/

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

/*-------COMMAND--------*/

void add_token_to_table(t_token **list_token, t_table_cmd **table)
{
	t_token *next;
	t_token *tmp;
	int		i;

	tmp = *list_token;
	i = 0;
	while (tmp != NULL && (tmp->key == e_word || tmp->key == e_single_quote || tmp->key == e_double_quote))
	{
		i++;
		tmp = tmp->next;
	}
	(*table)->arguments = (char **)malloc(sizeof(char *) * (i + 1));
	if ((*table)->arguments == NULL)
		return ;
	i = 0;
	while ((*list_token) != NULL && ((*list_token)->key == e_word || (*list_token)->key == e_single_quote || (*list_token)->key == e_double_quote))
	{
		next = (*list_token)->next;
		(*table)->arguments[i] = append_token_conect(list_token);
		i++;
	}
	(*table)->arguments[i] = NULL;
}

/*-------REDIRECTION--------*/

void redir_add_back(t_table_cmd **table, t_redir *new_redir)
{
	t_redir	*tmp;

	if (new_redir != NULL)
	{
		if ((*table)->redirections != NULL)
		{
			tmp = (*table)->redirections;
			while (tmp->next != 0)
				tmp = tmp->next;
			tmp->next = new_redir;
		}
		else
			(*table)->redirections = new_redir;
	}
}

/*-------REDIRECTION--------*/

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

void heredoc(t_redir *redir)
{
	char *line;
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return ; //!!!make return error!!!
	pid = fork();
	if (pid < 0)
		return ; //!!!make return error!!!
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			write(1, "heredoc> ", 9);
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(line, redir->name, ft_strlen(line) - 1) == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return ;
	close(fd[1]);
	waitpid(pid, NULL, 0);

	/* limiter = redir->name;
	redir->name = NULL;
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (line == NULL || ft_strncmp(limiter, line, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break ;
		}
		tmp_line = redir->name;
		redir->name = ft_strjoin(tmp_line, line);
		if (tmp_line)
			free(tmp_line);
	}
	free(limiter); */
}

/*-------REDIRECTION--------*/

t_redir *create_redir(t_token **list_token, int redir_type)
{
	t_redir *redirections;
	t_token *tmp_token;

	redirections = (t_redir *)malloc(sizeof(t_redir));
	if (redirections == NULL)
		return (NULL);
	redirections->type = redir_type;
	tmp_token = (*list_token)->next;
	token_destroy((*list_token));
	(*list_token) = tmp_token;
	redirections->name = append_token_conect(list_token);
	// heredoc
	if (redir_type == REDIR_HEREDOC)
	{
		heredoc(redirections);
	}
	return (redirections);
}

/*-------REDIRECTION--------*/

void inout_add_to_table(t_token **list_token, t_table_cmd **table)
{
	t_redir *redir_file;

	while ((*list_token) && (*list_token)->key == e_redir)
	{
		redir_file = create_redir(list_token, find_redir_type(*list_token));
		redir_add_back(table, redir_file);
	}
	
	/* if ((*list_token)->key == e_redir && !ft_strncmp((*list_token)->value, ">", 2))
	{
		redir_file = create_redir_file_token(list_token);
		token_add_back(&((*table)->out), redir_file);
	}
	else if ((*list_token)->key == e_redir && !ft_strncmp((*list_token)->value, ">>", 3))
	{
		redir_file = create_redir_file_token(list_token);
		token_add_back(&((*table)->out_append), redir_file);
	}
	else if ((*list_token)->key == e_redir && !ft_strncmp((*list_token)->value, "<", 2))
	{
		redir_file = create_redir_file_token(list_token);
		token_add_back(&((*table)->in), redir_file);
	}
	else if ((*list_token)->key == e_redir && !ft_strncmp((*list_token)->value, "<<", 3))
	{
		// heredoc
	} */
}

t_table_cmd *parser(t_token *list_token)
{
	t_table_cmd	*table;
	t_table_cmd	*head;
	t_token		*tmp;
	
	table = table_create();
	if (table == NULL)
		return (NULL);
	head = table;
	while (list_token)
	{
		if (list_token->key == e_word || list_token->key == e_single_quote || list_token->key == e_double_quote)
		{
			add_token_to_table(&list_token, &table);
		}
		if (list_token && list_token->key == e_redir)
		{
			inout_add_to_table(&list_token, &table);
		}
		if (list_token && list_token->key == e_pipe)
		{
			tmp = list_token->next;
			token_destroy(list_token);
			list_token = tmp;
			table->next = table_create();
			table = table->next;
		}
		/* if (list_token->key == e_word || list_token->key == e_single_quote || list_token->key == e_double_quote)
		{
			add_token_to_cmd(&list_token, &table);
			//cmd_add_back(&(table->commands), cmd);
		}
		if (list_token->key == e_redir)
		{
			inout_add_to_table(&list_token, &table);
		}
		else
		{
			// delete pipe token and bracket token
			tmp = list_token->next;
			token_destroy(list_token);
			list_token = tmp;
		} */
	}
	return (head);
}
