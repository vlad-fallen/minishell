/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:00:45 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/06 15:11:09 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
