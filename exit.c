#include "minishell.h"

int	check_argc_exit(char *str)
{
	int exit_status;

	exit_status = 0;
	if (ft_atoi(str) == 0 && str[0] != '0')
		exit_status = 2;
	else
		exit_status = ft_atoi(str);
	//printf("atoi = %d\n", ft_atoi(str));
	return (exit_status); //good
}

int	exit_prog(t_table_cmd *table)
{
	(void)table;
	if (table->arguments[1])
	{
		g_envp.status_exit = check_argc_exit(table->arguments[1]);
		//printf("g_envp.status_exit = %d\n", g_envp.status_exit);
	}
	if (table->arguments[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("zhs: exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	exit(g_envp.status_exit);
}