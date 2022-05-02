/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:16:56 by mbutter           #+#    #+#             */
/*   Updated: 2021/10/11 17:55:20 by mbutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (del == NULL)
		return ;
	if (*lst != NULL)
	{
		ft_lstclear(&(*lst)->next, del);
		del((*lst)->content);
		free(*lst);
		*lst = NULL;
	}
}
