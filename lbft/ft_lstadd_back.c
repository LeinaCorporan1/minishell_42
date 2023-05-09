/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:30:26 by lcorpora          #+#    #+#             */
/*   Updated: 2021/12/16 16:49:35 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list	**alst, t_list	*new)
{
	t_list	*add;

	if (!*alst)
		*alst = new;
	else
	{
		add = ft_lstlast(*alst);
		add -> next = &*new;
	}
}
