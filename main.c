/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:55:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/19 15:16:52 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_all_prog()
{
	rl_clear_history();
	exit(g_envp.status_exit);
}

int main()
{
	/* 
	line = readline("minishell> ");
	free(line);
	extern char **environ;

	if (environ == NULL)
		printf("NULL\n");
	else
		printf("not null\n");

	int i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i++]);
	} */
	char *line;
	t_token *list_token;
	t_table_cmd *table;

	env_init();
	g_envp.status_exit = EXIT_SUCCESS;
	all_signals();
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			exit_all_prog();
		}
		add_history(line);
		list_token = lexer(line);
		table = parser(list_token);
		executor(table);
		free(line);
	}
	exit (1);
}
