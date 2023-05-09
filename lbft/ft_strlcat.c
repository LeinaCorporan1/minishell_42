/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:49:56 by lcorpora          #+#    #+#             */
/*   Updated: 2023/01/11 12:23:05 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	src_len;
// 	size_t	dst_len;

// 	j = 0;
// 	dst_len = (int)ft_strlen(dst);
// 	src_len = (int)ft_strlen(src);
// 	i = dst_len;
// 	if (dstsize == 0)
// 		return (src_len);
// 	if (dstsize < dst_len)
// 		return (src_len + dstsize);
// 	else
// 	{
// 		while (src[j] && (dst_len + j) < dstsize)
// 			dst[i++] = src[j++];
// 		if ((dst_len + j) == dstsize && dst_len < dstsize)
// 			dst[--i] = '\0';
// 		else
// 			dst[i] = '\0';
// 		return (src_len + dst_len);
// 	}
// }
