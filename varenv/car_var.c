/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   car_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:39:00 by massavie          #+#    #+#             */
/*   Updated: 2023/02/21 11:23:52 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_car(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			i++;
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*since_car(char *buf, char c)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = count_since_car(buf, c);
	str = malloc(sizeof(char) * (x + 1));
	if (!str)
		return (buf);
	x = 0;
	while (buf[i] != '\0')
	{
		i++;
		if (buf[i] == c)
		{
			while (buf[i] != '\0')
				str[x++] = buf[i++];
		}
	}
	str[x] = '\0';
	return (str);
}

int	find_car_spe(char c)
{
	char	*car;
	int		i;

	car = ft_strdup("!#%+-./:=@[]^{}~*\0\'\"'");
	i = 0;
	while (car[i] != '\0')
	{
		if (c == ' ')
		{
			free (car);
			return (' ');
		}
		if (car[i] == c)
		{
			free (car);
			return (c);
		}
		i++;
	}
	free (car);
	return (0);
}

int	check_car_spe_doll(char *buf)
{
	int		i;
	char	car;

	i = 0;
	while (buf[i] != '\0')
	{
		if (i == 0 && (buf[i] >= '0' && buf[i] <= '9'))
			return (buf[i]);
		car = find_car_spe(buf[i]);
		if (car != 0)
			return (car);
		i++;
	}
	return (0);
}

int	count_since_car(char *buf, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!buf)
		return (0);
	x = 0;
	while (buf[i] != '\0' && buf[i] != c)
	{
		i++;
	}
	if (buf[i] == '\0')
		return (i);
	else
		i++;
	while (buf[i] != '\0')
	{
		x++;
		i++;
	}
	return (i);
}
