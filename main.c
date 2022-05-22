/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 12:55:00 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/22 16:28:45 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_all_prog()
{
	rl_clear_history();
	exit(g_envp.status_exit);
}

int	change_attributes(bool print_controls)
{
	int				err;
	struct termios	termios;

	err = tcgetattr(STDOUT_FILENO, &termios);
	if (err == -1)
		return (-1);
	if (print_controls)
		termios.c_lflag |= ECHOCTL;
	else
		termios.c_lflag &= ~(ECHOCTL);
	err = tcsetattr(STDOUT_FILENO, TCSANOW, &termios);
	if (err == -1)
		return (-1);
	return (0);
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
		if(line[0] != '\0')
		{
			list_token = lexer(line);
			table = parser(list_token);
			executor(table);
			free(line);
		}
	}
	exit (1);
}
