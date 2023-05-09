/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:39:05 by massavie          #+#    #+#             */
/*   Updated: 2023/02/20 16:08:45 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*since_sp(char *buf)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	if (buf == NULL)
		return (NULL);
	if (buf[i] != ' ' && buf != NULL)
		return (ft_str_ndup(buf));
	str = malloc(sizeof(char) * (count_since_sp(buf) + 1));
	if (!str)
		return (buf);
	x = 0;
	while (buf[i] != '\0' )
	{
		i++;
		if (buf[i - 1] == ' ' && buf[i] != ' ')
			while (buf[i] != '\0')
				str[x++] = buf[i++];
	}
	str[x] = '\0';
	return (str);
}

int	count_sep(char *str, char sep)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (str[j])
		if (str[j++] == sep)
			count++;
	return (count);
}

char	*ret_until_sp(char *untilsp)
{
	int		car;
	char	*split;

	car = check_car_spe_doll(untilsp);
	if (car != 0)
	{
		split = ft_split_char(untilsp, car);
		to_free(untilsp);
		return (split);
	}
	else
		return (untilsp);
}

char	*until_space(char *buf)
{
	int		i;
	char	*until;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i] != '\0' && buf[i] != ' ')
		i++;
	until = malloc(sizeof(char) * (i + 1));
	if (!until)
		return (NULL);
	i = 0;
	while (buf[i] != '\0' && buf[i] != ' ')
	{
		until[i] = buf[i];
		i++;
	}
	until[i] = '\0';
	return (ret_until_sp(until));
}

int	count_since_sp(char *buf)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (buf[i] != '\0')
	{
		i++;
		if (buf[i - 1] == ' ' && buf[i] != ' ')
		{
			while (buf[i] != '\0')
			{
				x++;
				i++;
			}
		}
	}
	return (x);
}
