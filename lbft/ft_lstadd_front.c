/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:02:18 by lcorpora          #+#    #+#             */
/*   Updated: 2021/12/16 16:50:37 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_front(t_list	**alst, t_list	*new)
{
	if (!alst || !new)
		return ;
	new -> next = *alst;
	*alst = new;
}
