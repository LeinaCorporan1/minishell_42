/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 08:29:13 by lcorpora          #+#    #+#             */
/*   Updated: 2021/12/07 13:36:37 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t num)
{
	size_t	i;
	char	*str;

	str = pointer;
	i = 0;
	while (i < num)
	{
		str[i] = value;
		i++;
	}
	return (str);
}
