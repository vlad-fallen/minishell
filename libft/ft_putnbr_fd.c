/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 12:17:37 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/11 17:58:55 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_putstr_fd("-2147483648", fd));
		ft_putchar_fd('-', fd);
		return (ft_putnbr_fd(-n, fd));
	}
	else if (n < 10)
		return (ft_putchar_fd((char)(n + '0'), fd));
	else
	{
		ft_putnbr_fd(n / 10, fd);
		return (ft_putnbr_fd(n % 10, fd));
	}
}
