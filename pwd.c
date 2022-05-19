/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:17:54 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/19 15:17:55 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char *str;

	str = NULL;
	str = getcwd(str, 0);
	if (str == NULL)
	{
		ft_putstr_fd("pwd failure\n", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	free(str);
	return (EXIT_SUCCESS);
}