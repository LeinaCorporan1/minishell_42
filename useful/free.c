/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:40:09 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 16:04:11 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tr(char ***tab)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strlen_triple(tab);
	if (!tab)
		return ;
	while (tab && tab[i] && i < max)
	{
		if (tab[i] != NULL)
			tab[i] = ft_free_dbl(tab[i]);
		i++;
	}
	free(tab);
}

char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i] != NULL)
	{
		if (tab[i] != NULL)
		{
			free (tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	if (tab)
		free(tab);
	return (NULL);
}

int	to_free(char *buf)
{
	if (buf)
		free (buf);
	return (1);
}

char	*str_null(char *str)
{
	if (str)
		free (str);
	return (NULL);
}

char	**ft_free_dbl(char **to_free)
{
	int	i;

	i = 0;
	if (!to_free)
		return (NULL);
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	return (NULL);
}
