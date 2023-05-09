/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:42:53 by lcorpora          #+#    #+#             */
/*   Updated: 2021/12/16 17:58:19 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*des;
	const char	*sr;

	des = dest;
	sr = src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		des[i] = sr[i];
		i++;
	}
	return (des);
}
