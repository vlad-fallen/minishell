/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:55:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/11 16:06:09 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_all_prog(void)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	rl_clear_history();
	exit(g_envp.status_exit);
}

void	main_prog(char *line)
{
	t_token		*list_token;
	t_table_cmd	*table;

	list_token = lexer(line);
	if (list_token != NULL)
		table = parser(&list_token);
	if (list_token == NULL && table != NULL)
		executor(table);
	free_table(&table);
}

int	main(void)
{
	char		*line;

	env_init();
	g_envp.status_exit = EXIT_SUCCESS;
	all_signals();
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$> ");
		if (!line)
			exit_all_prog();
		add_history(line);
		if (line[0] != '\0')
			main_prog(line);
		free(line);
	}
	free_global_env();
	exit (g_envp.status_exit);
}
