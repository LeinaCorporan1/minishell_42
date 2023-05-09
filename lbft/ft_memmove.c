/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:03:33 by lcorpora          #+#    #+#             */
/*   Updated: 2021/12/17 07:41:07 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void	*src, size_t len)
{
	size_t	i;
	char	*a;
	char	*b;

	i = 0;
	if (!dst && !src)
		return (NULL);
	a = (char *)dst;
	b = (char *)src;
	if (a > b)
	{
		while (i < len)
		{
			a[len - 1] = b[len - 1];
			len--;
		}
	}
	else
	{
		i = -1;
		while (++i < len)
			a[i] = b[i];
	}
	return (dst);
}
