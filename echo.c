/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:54:32 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/14 17:16:09 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_argc(t_table_cmd *table, int n_flag)
{
	int nbr;

	nbr = 0;
	while(table->commands->arguments[nbr])
		nbr++;
	if (n_flag == 1)
		nbr--;
	nbr--;
	return (nbr);
}

int	echo(t_table_cmd *table)
{
	int	n_flag;
	int	nbr_arguments;
	int	i;
	
	// printf("table->commands->arguments[0] %s\n", table->commands->arguments[0]);
	// printf("table->commands->arguments[1] %s\n", table->commands->arguments[1]);
	// printf("table->commands->arguments[2] %s\n", table->commands->arguments[2]);
	n_flag = 0;
	if (check_str(table->commands->arguments[1], "-n") && ft_strlen(table->commands->arguments[1]) == 2)
		n_flag = 1;
	// printf("n_flag = %d\n", n_flag);
	// printf("nbr_argc = %d\n", nbr_argc(table, n_flag));
	nbr_arguments = nbr_argc(table, n_flag);
	i = 1;
	if (n_flag == 1)
		i = 2;
	while (table->commands->arguments[i])
	{
		ft_putstr_fd(table->commands->arguments[i], 1);
		nbr_arguments--;
		if (nbr_arguments != 0)
			ft_putchar_fd(' ', 1);
		if (nbr_arguments == 0)
		{
			if (n_flag == 0)
				ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
