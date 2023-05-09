/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:18:51 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 16:19:42 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_split_syntax(char *buf)
{
	int	i;
	int	y;
	int	pos;

	y = 0;
	i = 0;
	pos = 0;
	while (buf != NULL && pos < (int)(int)ft_strlen(buf) && buf[pos])
	{
		y = quote_valid(buf + pos);
		if (y < 0)
			y = (int)ft_strlen(buf);
		while (y != (int)ft_strlen(buf) && buf[pos + y] != '\0' && (y == 0
				|| (y == 1 && buf[pos + y] != ' ') || buf[pos + y] == ' '))
			y++;
		pos = pos + y;
		i++;
	}
	return (i);
}
