/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:17:54 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/09 22:06:15 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_fun(void)
{
	char	*str;

	str = NULL;
	str = getcwd(str, 0);
	if (str == NULL)
	{
		ft_putstr_fd("pwd failure\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(str);
	str = NULL;
	return (EXIT_SUCCESS);
}
