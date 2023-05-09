/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:00:41 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/11 12:23:40 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

// int	ft_charcmp(char const c, char const *src)
// {
// 	size_t	j;

// 	j = 0;
// 	while (src[j])
// 	{
// 		if (src[j] == c)
// 			return (1);
// 		j++;
// 	}
// 	return (0);
// }

// char	*sadd(char const *str1, size_t first, size_t end, char *dst)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str1[first] && first <= end)
// 	{
// 		dst[i] = str1[first];
// 		first++;
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }

// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	size_t	beg;
// 	size_t	last;
// 	size_t	i;
// 	char	*dest;

// 	i = 0;
// 	if (!s1)
// 		return (NULL);
// 	if (!set)
// 		return ((char *)s1);
// 	while (s1[i] && ft_charcmp(s1[i], set))
// 		i++;
// 	beg = i;
// 	i = (int)ft_strlen(s1) - 1;
// 	while (i > beg && ft_charcmp(s1[i], set))
// 		i--;
// 	last = i;
// 	dest = (char *)malloc(sizeof(char) *(last - beg) + 2);
// 	if (!dest)
// 		return (NULL);
// 	dest = sadd(s1, beg, last, dest);
// 	return (dest);
// }
