/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qte_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:36:35 by massavie          #+#    #+#             */
/*   Updated: 2023/02/20 14:11:02 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_quote(char *str, int i, t_mini *mini)
{
	while (str[i] != '\0')
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34)
			{
				i++;
				if (str[i] < 48 || str[i] > 57)
				{
					ft_error("Error\n");
					g_ret = 255;
					exit (255);
				}
				ft_quote(str, i, mini);
			}
		}
	}
	return (0);
}

char	*ft_split_quote(char *str, char c)
{
	char	*split;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	split = malloc(sizeof(char) * (i + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		split[i] = str[i];
		i++;
	}
	split[i] = '\0';
	if (str[i] == '\0')
	{
		ft_error ("Quote >\n");
	}
	return (split);
}

int	parse_quote(char *buf)
{
	int		i;
	char	*str;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i] != '\0')
	{
		if (buf[i] == 34 || buf[i] == 39)
		{
			str = ft_split_quote(buf + 1 + i, buf[i]);
			check_number(str);
			i += (int)ft_strlen(str) + 1;
			free (str);
		}
		i++;
		if (i > (int)ft_strlen(buf))
			return (0);
	}
	return (0);
}
