/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:21:18 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/12 12:30:17 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_arr(char **arr, size_t max)
{
	size_t	i;

	i = 0;
	while (i < max)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_do_split(char **arr, const char *s, char c)
{
	size_t	i;
	size_t	len;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] == c)
			i++;
		while (s[i + len] != c && s[i + len])
			len++;
		if (len == 0)
			break ;
		arr[j] = ft_substr(&s[i], 0, len);
		if (arr[j] == NULL)
		{
			ft_free_arr(arr, j);
			break ;
		}
		j++;
		i += len;
	}
}

int	ft_get_count(const char *s, char c)
{
	size_t	word_count;
	size_t	i;

	i = 0;
	if (s[i] != c && s[i] != '\0')
	{
		word_count = 1;
	}
	else
		word_count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] == '\0')
				break ;
			word_count++;
		}
		i++;
	}
	return (word_count);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	word_count;

	arr = NULL;
	if (s != NULL)
	{
		word_count = ft_get_count(s, c);
		arr = (char **)malloc(sizeof(char *) * (word_count + 1));
		if (arr != NULL)
		{
			arr[word_count] = NULL;
			ft_do_split(arr, s, c);
		}
	}
	return (arr);
}
