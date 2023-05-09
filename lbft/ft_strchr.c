/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:02:39 by lcorpora          #+#    #+#             */
/*   Updated: 2021/12/16 16:54:39 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char	*str, int c)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
		{
			res = (char *)str + i;
			return (res);
		}
		i++;
	}
	if (str[i] == (unsigned char)c)
	{
		res = (char *)str + i;
		return (res);
	}
	return (NULL);
}
