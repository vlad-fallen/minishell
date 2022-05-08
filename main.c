/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:55:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/08 15:02:54 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_exit(void)
{
	write(1, "exit\n", 5);
	return (1);
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
		signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_prog);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_prog);
		line = readline("minishell$>");
		if (!line)
		{
			return (print_exit());
		}
		add_history(line);
		list_token = lexer(line);
		print_list_token(list_token);
		list_token = dollar_pars(list_token);
		//print_list_token(list_token);
		table = parser(list_token);
		free(line);
	}
}
