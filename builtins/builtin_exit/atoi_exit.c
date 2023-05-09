/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:36:45 by massavie          #+#    #+#             */
/*   Updated: 2023/01/11 11:32:08 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_atoi_uns(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\r' || str[i] == ' '
		|| str[i] == 34 || str[i] == 39)
		i++;
	return (i);
}

int	ft_atoi_ex(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\r' || str[i] == ' ')
		i++;
	return (i);
}

void	ft_atoi_unsigned(const char *str)
{
	int					i;
	int					neg;
	unsigned long long	nbr;

	neg = 1;
	nbr = 0;
	i = ft_atoi_uns(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
		nbr = nbr * 10 + (str[i++] - 48);
	if (nbr > 9223372036854775807)
	{
		ft_error ("Too much long for long long type\n");
		g_ret = 255;
		exit (255);
	}
}

long long	ft_atoi_exit(const char *str)
{
	int			i;
	int			neg;
	long long	nbr;

	i = ft_atoi_ex(str);
	neg = 1;
	nbr = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while ((str[i] > 47 && str[i] < 58) || str[i] == 34 || str[i] == 39)
	{
		if (str[i] != 34 && str[i] != 39)
			nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (neg * nbr);
}
