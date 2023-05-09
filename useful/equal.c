/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:41:51 by massavie          #+#    #+#             */
/*   Updated: 2023/01/11 09:58:21 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_equal(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (-1);
	while (buf[i] != '\0')
	{
		if (buf[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	position_equal(char *buf)
{
	int	i;

	i = 0;
	while (buf && buf[i] != '\0')
	{
		if (buf[i] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*until_equal(char *buf)
{
	int		i;
	char	*until;

	i = -1;
	if (!buf)
		return (0);
	if (check_equal(buf) == -1)
		return (0);
	until = malloc(sizeof(char) * (position_equal(buf) + 1));
	if (!until)
		return (0);
	while (buf[++i] != '\0')
	{
		if (buf[i] == '=')
		{
			until[i] = '\0';
			return (until);
		}
		until[i] = buf[i];
	}
	until[i] = '\0';
	free (until);
	return (NULL);
}
