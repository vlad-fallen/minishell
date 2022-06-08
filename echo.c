/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:54:32 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/08 21:27:13 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_argc(t_table_cmd *table)
{
	int	nbr;

	nbr = 0;
	while (table->arguments[nbr])
		nbr++;
	return (nbr);
}

int	all_n(char *argm)
{
	int	i;

	i = 0;
	if (argm[0] == '-' && ft_strlen(argm) == 1)
		return (0);
	argm++;
	while (argm[i])
	{
		if (argm[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_help(t_table_cmd *table, int n_flag, int i)
{
	int	j;
	int	nbr_arg;

	j = 0;
	while (table->arguments[j])
	{
		if (!check_str(table->arguments[j], "-n"))
			break ;
		j++;
	}
	i = i + j;
	nbr_arg = nbr_argc(table) - i;
	while (table->arguments[i])
	{
		ft_putstr_fd(table->arguments[i], STDOUT_FILENO);
		nbr_arg--;
		if (nbr_arg != 0)
			ft_putchar_fd(' ', STDOUT_FILENO);
		if (nbr_arg == 0)
		{
			if (n_flag == 0)
				ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
}

int	echo_check(t_table_cmd *table)
{
	if (!table->arguments[1])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	if (table->arguments[1][0] == '\0' && nbr_argc(table) == 2)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	return (1);
}

int	echo(t_table_cmd *table)
{
	int	n_flag;
	int	i;
	int	j;

	if (!echo_check(table))
		return (EXIT_SUCCESS);
	n_flag = 0;
	i = 1;
	j = 1;
	while (table->arguments[j] && check_str(table->arguments[j], "-n"))
	{
		if (check_str_red(table->arguments[j], "-n")
			&& all_n(table->arguments[j]))
		{
			n_flag = 1;
			i++;
		}
		j++;
	}
	echo_help(table, n_flag, i);
	return (EXIT_SUCCESS);
}
