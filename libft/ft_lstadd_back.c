/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:23:37 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/11 17:54:28 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (new != NULL)
	{
		if (*lst != NULL)
		{
			tmp = *lst;
			while (tmp->next != 0)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			*lst = new;
	}
}
