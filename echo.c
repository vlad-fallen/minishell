/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:54:32 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/10 16:10:01 by echrysta         ###   ########.fr       */
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
	// int	n_flag;
	// int	nbr_arguments;
	// int	i;
	
	// n_flag = 0;
	// if (check_str(table->commands->arguments[1], "-n"))
	// 	n_flag = 1;
	// //printf("n_flag = %d\n", n_flag);
	// //printf("nbr_argc = %d\n", nbr_argc(table, n_flag));
	// nbr_arguments = nbr_argc(table, n_flag);
	// i = 1;
	// if (n_flag == 1)
	// 	i = 2;
	// while (table->commands->arguments[i])
	// {
	// 	printf("%s", table->commands->arguments[i]);
	// 	nbr_arguments--;
	// 	if (nbr_arguments != 0)
	// 		printf(" ");
	// 	if (nbr_arguments == 0)
	// 	{
	// 		if (n_flag == 0)
	// 			printf("\n");	
	// 	}
	// 	i++;
	// }
	printf("table->commands->arguments[0] %s\n", table->commands->arguments[0]);
	printf("table->commands->arguments[1] %s\n", table->commands->arguments[1]);
	printf("table->commands->arguments[2] %s\n", table->commands->arguments[2]);
	exit(0);
}
