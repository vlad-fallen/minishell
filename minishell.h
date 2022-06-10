/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:31:33 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/10 21:12:09 by echrysta         ###   ########.fr       */
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
# include <dirent.h>
# include <limits.h>
# include "libft.h"


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
	char			*name;
	int				type;
	int				fd;
	int				quote_flag;
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

typedef struct s_val_and_key
{
	char	*key;
	char	*value;
	int		plus;
}	t_val_and_key;

t_info	g_envp;

/* env */
void		env_init(void);
t_env_var	*envlist_new(char *key, char *value);
void		envlist_add_back(t_env_var **lst, t_env_var *new);
void		free_global_env(void);


/* tokens */
t_token	*token_new(key_token key, char *value);
void	token_add_back(t_token **lst, t_token *new);
void	token_destroy(t_token **token);
void	token_destroy_all(t_token **token);
void	del_elem(t_token *del, t_token *head);

/* lexer */
int		ft_quotelen(char *str);
int		ft_wordlen(char *str);
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
t_table_cmd	*table_create(void);
void		add_token_to_table(t_token **list_token, t_table_cmd **table);
void		inout_add_to_table(t_token **list_token, t_table_cmd **table);
char		*append_token_conect(t_token **list_token);
void		free_table_redir(t_redir **redir);
void		free_table(t_table_cmd **table);

/* pasing */
t_table_cmd	*parser(t_token **list_token);

/* dollar_exit_status */
t_token	*dollar_exit_status(t_token *list_token);

/* dollar_pars */
t_token	*dollar_pars(t_token *list_token);

/* dollar_pars_2 */
char	*change_value(char *value, char *old, int len_sp_val, char *env_value);
char	*digit_arg_dol(char *value, char *old_value);

/* dollar_pars_3 */
t_token	*del_elem_list(t_token *del, t_token **head);
char 	*del_posle_dol(char *old_value, char *value);

/* dollar_pars_utils */
int		check_str_red(char *str1, char *str2);
int		check_str_n(char *str1, char *str2, int n);
int		check_str(char *str1, char *str2);
int		correct_count(char *elem_split_value);
char	*correct_dollar_pos(char *value);

/* dollar_pars_utils_2 */
int	count_token(t_token *list_token);
int	check_str_for_clean(char *str1, char *str2);

/* expand_prog */
t_token	*expand_prog(t_token *list_token);

/* executor */
void	stream_op(int *initial_stdin, int *initial_stdout, int mode);
void	exec_wait_one(int proc_id);
int		make_fork(pid_t *proc_id);
int		exec_proc(char **cmd, char **envp);
int		execute_redirect(t_table_cmd *table);
void	exec_wait_all(int proc_id, int *stdin_dup, int *stdout_dup);
void	exec_scmd(t_table_cmd *table);
void	exec_pipe(t_table_cmd *table);
void	executor(t_table_cmd *table);

/* builtin */
int			check_builtin(t_table_cmd *table);
void		run_builtin(t_table_cmd *table);

/* echo */
int			echo(t_table_cmd *table);

/* cd */
int	cd_fun(t_table_cmd *table);

/* cd_utils */
int			local_cd_exit(int exit_status, char **cwd, t_table_cmd *table);
t_env_var	*find_key(t_env_var	*env_init_tmp, char *which_pwd);

/* pwd */
int			pwd_fun(void);

/* export */
int			export_fun(t_table_cmd *table);
void		add_elem_env_help(t_env_var *env_list, char *key, char *value);
void		change_val_ex(t_env_var	*list, char *val);
void		change_val_ex_plus(t_env_var	*list, char *val);
int			check_argc(char *str);
int			find_plus(char *str);
t_env_var	*envlist_new_alone(char	*key);
void		print_sorted_e(t_env_var *env);
void		update_env(t_env_var *env_list);

/* unset */
int			unset_fun(t_table_cmd *table);
void		del_add_elem_env(char	*str, t_env_var	*env_list);

/* env */
int 		env(void);
void		print_list_env(t_env_var *list_token);

/* exit */
int			exit_prog(t_table_cmd *table);

/* utils */
void	arr_free(char ***arr);
int		print_error(char *shell_name, char *cmd, char *arg, char *message);
void	free_and_exit(int status, t_table_cmd **table);
void	print_list_token(t_token *list_token);
void	print_list_arguments(char **arg);


#endif
