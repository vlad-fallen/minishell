/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:31:33 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/04 20:56:05 by mbutter          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft.h"

# include <dirent.h> //?

# define REDIR_OUT 1
# define REDIR_IN 2
# define REDIR_APPEND 3
# define REDIR_HEREDOC 4

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_info
{
	char		**env;
	t_env_var	*env_list;
	int			status_exit;
}	t_info;

typedef enum e_key_token
{
	e_white_space,
	e_word,
	e_single_quote,
	e_double_quote,
	e_redir,
	e_redir_file,
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

typedef struct s_redir
{
	// t_token				*arguments;
	// заменил структуру на массив строк для экзекьютура
	char			*name;
	int				type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_table_cmd
{
	char				**arguments;
	t_redir				*redirections;
	int					stream_in;
	int					stream_out;
	struct s_table_cmd	*next;
}	t_table_cmd;

t_info	g_envp;

/* env */
void		env_init(void);
t_env_var	*envlist_new(char *key, char *value);
void		envlist_add_back(t_env_var **lst, t_env_var *new);
void		free_global_env(void);


/* tokens */
t_token	*token_new(key_token key, char *value);
void	token_add_back(t_token **lst, t_token *new);
void	token_destroy(t_token *token);
void	token_destroy_all(t_token *token);
void	del_elem(t_token *del, t_token *head); //для удаления токена

/* lexer */
int		ft_quotelen(char *str);
int		ft_wordlen(char *str);
void	find_duplicate_flags(t_token **list_token); // для исключения повторяющихся флагов
int		lexer_token_whitespace(char *input, int *i, t_token **list_token);
int		lexer_token_pipe(char *input, int *i, t_token **list_token);
int		lexer_token_bracket(char *input, int *i, t_token **list_token);
int		lexer_token_redir(char *input, int *i, t_token **list_token);
int		lexer_token_quote(char *input, int *i, t_token **list_token);
int		lexer_token_word(char *input, int *i, t_token **list_token);
t_token	*lexer(char *input);

/* signal */
void	sig_prog(int sig);
void	all_signals(void);

/* table struct */
t_table_cmd *table_create(void);
void add_token_to_table(t_token **list_token, t_table_cmd **table);
void inout_add_to_table(t_token **list_token, t_table_cmd **table);
char *append_token_conect(t_token **list_token);
void	free_table_redir(t_redir **redir);
void free_table(t_table_cmd **table);

/* pasing */
t_table_cmd	*parser(t_token *list_token);

/* dollar_pars */
t_token		*dollar_pars(t_token *list_token);
t_token		*dollar_exit_status(t_token *list_token);
char		*digit_arg_dol(char *value, char *old_value);
int			check_str(char *str1, char *str2);
char		*change_in_env(char *value, int flag_ex);
char		*change_value(char *value, char *old, int len_sp_val, char *env_value);
int			check_asc(char *change_value);
char 		*del_posle_dol(char *old_value, char *value);
char		*digit_arg_dol(char *value, char *old_value);
int			correct_count(char *elem_split_value);
int			check_str_n(char *str1, char *str2, int n);
t_token		*del_elem_list(t_token *del, t_token *head);
int			check_str_red(char *str1, char *str2);

/* expand_prog */
t_token	*expand_prog(t_token *list_token);

/* executor */
void	stream_op(int *initial_stdin, int *initial_stdout, int mode);
int		make_fork(pid_t *proc_id);
int		exec_proc(char **cmd, char **envp);
void	execute_redirect(t_table_cmd *table);
void	exec_scmd(t_table_cmd *table);
void	executor(t_table_cmd *table);

/* builtin */
int		check_builtin(t_table_cmd *table);
void	run_builtin(t_table_cmd *table);
int		echo(t_table_cmd *table);
int		cd(t_table_cmd *table);
int		pwd(void);
int		export_fun(t_table_cmd *table);
int		unset_fun(t_table_cmd *table);
int 	env(void);
void	print_list_env(t_env_var *list_token);
int		exit_prog(t_table_cmd *table);

/* utils */
void	arr_free(char ***arr);
int		print_error(char *shell_name, char *cmd, char *arg, char *message);
void	free_and_exit(int status, t_table_cmd **table);

/* для тестов*/
void	print_list_token(t_token *list_token);
void	print_list_arguments(char **arg);


#endif
