/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:43:12 by massavie          #+#    #+#             */
/*   Updated: 2023/01/11 06:52:32 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_split_one(char *str, char c)
{
	char	*split;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
	}
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
	return (split);
}

char	*ft_cut(char *str, char c)
{
	char	*split;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
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
	return (split);
}

char	*ft_split_char(char *str, char c)
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
	return (split);
}
