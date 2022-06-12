/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:55:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/12 12:52:38 by mbutter          ###   ########.fr       */
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
	rl_outstream = stderr;
	while (1)
	{
		all_signals();
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
