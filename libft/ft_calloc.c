/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:52:54 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/07 18:25:09 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t s)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = (void *)malloc(n * s);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, n * s);
	return (ptr);
}
