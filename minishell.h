/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:48:34 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/03 19:20:59 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

typedef struct s_env_var
{
	char	            *key;
	char	            *value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_info
{
	char	    **env;
	t_env_var	*env_list;
	int		    status_exit;
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
	int				connect;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd_arg
{
	t_token				*arguments;
	struct s_cmd_arg	*next;
}	t_cmd_arg;

typedef struct s_table_cmd
{
	t_cmd_arg	*arguments;
	char		**in;
	char		**out;
}	t_table_cmd;

t_info	g_envp;

void env_init(void);

/* tokens */
t_token	*token_new(key_token key, char *value);
void	token_add_back(t_token **lst, t_token *new);
void	token_destroy(t_token *token);

/* lexer */
int     ft_quotelen(char *str);
int     ft_wordlen(char *str);
int     lexer_token_whitespace(char *input, int *i, t_token **list_token);
int     lexer_token_pipe(char *input, int *i, t_token **list_token);
int     lexer_token_bracket(char *input, int *i, t_token **list_token);
int     lexer_token_redir(char *input, int *i, t_token **list_token);
int     lexer_token_quote(char *input, int *i, t_token **list_token);
int     lexer_token_word(char *input, int *i, t_token **list_token);
t_token *lexer(char *input);

/* signal */
void	sig_prog(int sig);

/* pasing */
t_token     *dollar_pars(t_token *list_token);
t_table_cmd *parser(t_token *list_token);

/* для тестов*/
void	print_list_token(t_token *list_token);
void	print_list_env(t_env_var *list_token);

#endif
