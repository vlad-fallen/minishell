/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:04:13 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/10 21:04:11 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long	value_exit(char	*str)
{
	int				i;
	unsigned long	nbr;
	int				minus;

	i = 0;
	minus = 1;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	nbr = 0;
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + str[i] - 48;
		if ((minus == 1 && nbr > LONG_MAX)
			|| (minus == -1 && nbr > (unsigned long)(LONG_MAX + 1UL)))
			exit (255);
		i++;
	}
	return ((long)(minus * nbr));
}

int	check_argc_exit(char *str)
{
	if (ft_atoi(str) == 0 && str[0] != '0'
		&& !check_str(str, "-9223372036854775808"))
	{
		if (check_str("+0", str))
			return (0);
		return (255);
	}
	else
		return (value_exit(str));
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
	if (count >= 2)
		g_envp.status_exit = check_argc_exit(table->arguments[1]);
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
