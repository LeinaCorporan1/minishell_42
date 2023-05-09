/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:43:58 by lcorpora          #+#    #+#             */
/*   Updated: 2021/12/16 16:51:04 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*li;
	t_list	*stock;

	li = *lst;
	while (li != NULL)
	{
		stock = li -> next;
		ft_lstdelone(li, del);
		li = stock;
	}
	*lst = NULL;
}
