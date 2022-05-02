/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:58:34 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/07 13:29:31 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && n > 0)
	{
		if (str1[i] != str2[i])
			break ;
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
