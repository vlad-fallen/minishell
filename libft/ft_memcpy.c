/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:56:28 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/07 11:58:22 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *str, size_t n)
{
	int	i;

	i = 0;
	if ((!dest && !str) || (n == 0) || (dest == str))
		return (dest);
	while (n > 0)
	{
		((char *)dest)[i] = ((char *)str)[i];
		i++;
		n--;
	}
	return (dest);
}
