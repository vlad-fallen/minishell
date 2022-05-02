/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:59:34 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/11 18:43:08 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;
	size_t	len_src;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	i = 0;
	j = len_dest;
	if (size > 0)
	{
		while (src[i] != '\0' && j < (size - 1))
		{
			dest[j] = src[i];
			i++;
			j++;
		}
		if (len_dest < size)
			dest[j] = '\0';
	}
	if (len_dest > size)
		len_dest = size;
	return (len_dest + len_src);
}
