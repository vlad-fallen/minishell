#include "minishell.h"

int	check_argc_exit(char *str)
{
	//printf("str = %s\n", str);
	if (check_str(str, "9223372036854775809"))
		return (255);
	if (check_str(str, "-9223372036854775808"))
		return (0);
	if ((ft_atoi(str) == 0 && str[0] != '0'))
	{
		if (check_str("+0", str))
			return (0);
		//printf(" 1 str = %s, ft_atoi = %d\n", str, ft_atoi(str));
		return (255);
	}
	else
	{
		//printf("2 str = %s, ft_atoi = %d\n", str, ft_atoi(str));
		return ((unsigned char)ft_atoi(str)); //good
	}
}

int	count_arg(char **str)
{
	int	count;
	
	count = 0;
	while (str[count])
		count++;
	return (count);
}

int	exit_prog(t_table_cmd *table)
{
	int	count;

	count = count_arg(table->arguments);
	//printf("count = %d\n", count);
	if (count >= 2)
	{
		g_envp.status_exit = check_argc_exit(table->arguments[1]);
		//printf("g_envp.status_exit = %d\n", g_envp.status_exit);
		//printf("g_envp.status_exit = %d\n", g_envp.status_exit);
	}
	if (count >= 3)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("zhs: exit: too many arguments\n", 2);
		if (g_envp.status_exit != 255)
			g_envp.status_exit = 1;
		return (g_envp.status_exit);
	}
	ft_putstr_fd("exit\n", 2);
	exit(g_envp.status_exit);
	return (g_envp.status_exit);
}
