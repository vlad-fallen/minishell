/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:48:34 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/02 15:06:37 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

typedef struct s_env_var
{
	char	*key;
	char	*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_info
{
	char	**env;
	t_env_var	*env_list;
	int		status_exit;
}	t_info;

typedef enum e_key_token
{
	e_white_space,
	e_word,
	e_single_quote,
	e_double_quote,
	e_redir,
	e_pipe,
	e_left_bracket,
	e_right_bracket
}	key_token;

typedef struct s_token
{
	key_token		key;
	char			*value;
	struct s_token	*next;
}	t_token;


t_info	g_envp;

void env_init(void);

t_token	*token_new(key_token key, char *value);
void	token_add_back(t_token **lst, t_token *new);
void	token_destroy(t_token *token);

#endif