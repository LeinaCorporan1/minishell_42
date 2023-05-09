/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:38:37 by massavie          #+#    #+#             */
/*   Updated: 2023/01/11 12:07:16 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_tab(char **tabl)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (tabl[i] != NULL)
	{
		len += (int)ft_strlen(tabl[i]);
		i++;
	}
	return (len);
}

int	count_str_split(char *str, char sep)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
		if (str[i++] == sep)
			count++;
	return (count);
}

int	count_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		i++;
	}
	return (i);
}
