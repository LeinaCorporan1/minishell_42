/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:42 by massavie          #+#    #+#             */
/*   Updated: 2023/01/11 06:40:18 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//ok

char	*until_colon(char *path)
{
	int		i;
	char	*str;

	i = 0;
	if (!path)
		return (NULL);
	while (path && path[i] != ':')
	{
		i++;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (path && path[i] != ':')
	{
		str[i] = path[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	new_colon(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (0);
	while (path[i] != '\0')
	{
		if (path[i] == ':')
			return (1);
		i++;
	}
	return (0);
}

int	new_slash(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (0);
	while (path[i] != '\0')
	{
		if (path[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	free_dir_bin(char *dir, char *bin)
{
	if (dir)
		free (dir);
	if (bin)
		free (bin);
}
