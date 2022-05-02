/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:11:18 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/07 17:10:34 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (*to_find == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		n = 0;
		while ((str[i + n] == to_find[n]) && (i + n < len))
		{
			if (to_find[n + 1] == '\0')
				return ((char *)str + i);
			n++;
		}
		i++;
	}
	return (NULL);
}
