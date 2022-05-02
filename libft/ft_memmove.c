/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:49:22 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/07 12:02:44 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if ((!dest && !src) || (n == 0) || (dest == (void *)src))
		return (dest);
	if (src < dest)
	{
		i = 1;
		while (i <= n)
		{
			((char *)dest)[n - i] = ((char *)src)[n - i];
			i++;
		}
	}
	else
	{
		i = 0;
		while (n > 0)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
			n--;
		}
	}
	return (dest);
}
