/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:55:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/10 21:06:43 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_info	g_envp;

void	exit_all_prog()
{
	rl_clear_history();
	exit(g_envp.status_exit);
}

int main()
{
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
		if(line[0] != '\0')
		{
			list_token = lexer(line);
			if (list_token != NULL)
				table = parser(&list_token);
			if (list_token == NULL && table != NULL)
				executor(table);
			free_table(&table);
		}
		free(line);
	}
	free_global_env();
	exit (g_envp.status_exit);
}
