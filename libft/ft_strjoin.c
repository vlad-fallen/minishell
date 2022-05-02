/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:59:43 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/11 18:44:24 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;

	str = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (str != NULL)
		{
			ft_memmove(str, s1, ft_strlen(s1));
			ft_memmove(str + ft_strlen(s1), s2, ft_strlen(s2));
			str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
		}
	}
	else if (s1 == NULL)
		str = ft_strdup(s2);
	else if (s2 == NULL)
		str = ft_strdup(s1);
	return (str);
}
