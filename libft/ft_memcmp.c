/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:26:47 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/06 17:00:39 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned long	i;

	i = 0;
	while (n > 0)
	{
		if (((unsigned char *)str1)[i] != ((unsigned char *)str2)[i])
			break ;
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
}
