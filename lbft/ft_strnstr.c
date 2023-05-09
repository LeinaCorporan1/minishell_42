/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:15:18 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/11 12:24:41 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// char	*ft_strnstr(const char *big, const char *little, size_t len)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*res;

// 	i = 0;
// 	if (little[i] == '\0')
// 		return ((char *)big);
// 	while (big[i] && i < len)
// 	{
// 		j = 0;
// 		while (big[i + j] != '\0' && little[j] == big[i + j] && i + j < len)
// 			j++;
// 		if (j == (int)ft_strlen(little))
// 		{
// 			res = (char *)(big + i);
// 			return (res);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }
