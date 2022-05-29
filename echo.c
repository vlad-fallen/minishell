/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:54:32 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/29 13:57:56 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_argc(t_table_cmd *table)
{
	int nbr;

	nbr = 0;
	while(table->arguments[nbr])
		nbr++;
	return (nbr);
}

int	all_n(char *argm)
{
	int i;

	i = 0;
	if (argm[0] == '-' && ft_strlen(argm) == 1)
		return (0);
	argm++;
	while (argm[i])
	{
		if (argm[i] != 'n')
			return (0); //плохо
		i++;
	}
	return (1); //хоррошо
}

int	echo(t_table_cmd *table)
{
	int	n_flag;
	int	nbr_arguments;
	int	i;
	int j;

	if (!table->arguments[1])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	if (table->arguments[1][0] == '\0')
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	n_flag = 0;
	i = 1;
	j = 1;
	while (table->arguments[j] && check_str(table->arguments[j], "-n"))
	{
		if (check_str(table->arguments[j], "-n") && all_n(table->arguments[1]))
		{
			n_flag = 1;
			i++;
		}
		j++;
	}
	j = 0;
	while (table->arguments[j])
	{
		if (!check_str(table->arguments[j], "-n"))
			break;	
		j++;
	}
	i = i + j;
	nbr_arguments = nbr_argc(table);
	nbr_arguments = nbr_arguments - i;
	// printf("j = %d\n", j);
	// print_list_arguments(table->arguments);
	// printf("nbr_arguments = %d\n", nbr_arguments);
	// printf("n_flag = %d\n", n_flag);
	// printf("i = %d\n", i);
	while (table->arguments[i])
	{
		ft_putstr_fd(table->arguments[i], STDOUT_FILENO);
		nbr_arguments--;
		if (nbr_arguments != 0)
			ft_putchar_fd(' ', STDOUT_FILENO);
		if (nbr_arguments == 0)
		{
			if (n_flag == 0)
				ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
