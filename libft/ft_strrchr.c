/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:43:22 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/08 10:56:29 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
		{
			ptr = &((char *)str)[i];
			break ;
		}
		i--;
	}
	return (ptr);
}
