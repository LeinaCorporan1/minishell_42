/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:24:17 by lcorpora          #+#    #+#             */
/*   Updated: 2021/12/16 16:48:20 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*dst;

	if (!lst)
		return (NULL);
	new = 0;
	while (lst)
	{
		dst = ft_lstnew(f(lst -> content));
		if (!dst)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, dst);
		lst = lst -> next;
	}
	return (new);
}
