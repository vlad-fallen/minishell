/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:23:04 by mbutter           #+#    #+#             */
/*   Updated: 2022/02/02 18:15:28 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_buf(int fd, char *str)
{
	char	buf[BUFFER_SIZE + 1];
	int		r;
	char	*tmp;

	r = read(fd, buf, BUFFER_SIZE);
	while (r > 0)
	{
		buf[r] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(str, '\n'))
		{
			break ;
		}
		r = read(fd, buf, BUFFER_SIZE);
	}
	return (str);
}

static char	*ft_get_line(char *str_buf)
{
	char	*str;
	size_t	i;

	i = 0;
	if (str_buf[i] == '\0')
		return (NULL);
	while (str_buf[i] && str_buf[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (str_buf[i] && str_buf[i] != '\n')
	{
		str[i] = str_buf[i];
		i++;
	}
	if (str_buf[i] == '\n')
	{
		str[i] = str_buf[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_get_new_line(char *str_buf)
{
	char	*new_buf;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str_buf[i] && str_buf[i] != '\n')
		i++;
	if (!str_buf[i])
	{
		free(str_buf);
		return (NULL);
	}
	new_buf = (char *)malloc(sizeof(char) * (ft_strlen(str_buf) - i + 1));
	if (!new_buf)
		return (NULL);
	i++;
	while (str_buf[i])
	{
		new_buf[j++] = str_buf[i++];
	}
	new_buf[j] = '\0';
	free(str_buf);
	return (new_buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str_buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str_buf = get_buf(fd, str_buf);
	if (!str_buf)
		return (NULL);
	line = ft_get_line(str_buf);
	str_buf = ft_get_new_line(str_buf);
	return (line);
}
