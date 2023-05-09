/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:02 by massavie          #+#    #+#             */
/*   Updated: 2023/02/20 14:12:48 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nocar(char *buf, char *until, char *bufsplit)
{
	(void) buf;
	if (until)
		free (until);
	ft_error ("bash : export : ");
	ft_error (bufsplit);
	ft_error (" : not a valid identifier\n");
	g_ret = 1;
	return (1);
}

int	notvalid_car(char *buf, char *bufsplit)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i] != '\0')
	{
		if (i == 0)
		{
			if (buf[i] >= '0' && buf[i] <= '9')
				return (nocar(buf, NULL, bufsplit));
		}
		if ((buf[i] < 97 || buf[i] > 122) && (buf[i] < 65 || buf[i] > 90)
			&& (buf[i] < 48 || buf[i] > 57) && (buf[i] != 95) && (buf[i] != 92))
			return (nocar(buf, NULL, bufsplit));
		i++;
	}
	return (0);
}

char	*until_equal_no_car(char *buf)
{
	int		i;
	char	*until;

	i = -1;
	if (!buf)
		return (0);
	if (check_equal(buf) == -1)
		return (ft_str_ndup(buf));
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
	return (ft_str_ndup(buf));
}
