/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 11:17:49 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/11 18:09:13 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			str_len;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (len > str_len)
		len = str_len;
	if (start > (unsigned int)str_len)
		start = (unsigned int)str_len;
	if (start + len > str_len)
		len = str_len - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ft_memmove(str, s + start, len);
	str[len] = '\0';
	return (str);
}
