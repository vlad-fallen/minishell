/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:50:34 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/08 10:39:51 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t num)
{
	int		i;
	void	*ptr;

	i = 0;
	ptr = NULL;
	while (num > 0)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
		{
			ptr = &((void *)str)[i];
			break ;
		}
		i++;
		num--;
	}
	return (ptr);
}
