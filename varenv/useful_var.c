/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:27:37 by massavie          #+#    #+#             */
/*   Updated: 2023/02/22 18:12:41 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*echodoll(void)
{
	char	*buf;

	buf = ft_itoa(g_ret);
	return (buf);
}

void	freestrsplitdoll(char *str_esp, char *until_sp)
{
	free(str_esp);
	free (until_sp);
}

char	*string_var(char **tabl)
{
	int		i;
	char	*all;

	i = 0;
	all = NULL;
	if (!tabl)
		return (NULL);
	while (tabl[i] != NULL)
	{
		all = ft_strjoin(all, tabl[i]);
		i++;
	}
	return (all);
}

int	check_doll(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i] != '\0')
	{
		if (buf[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	check_num_first(char *stresp)
{
	char	*num;
	int		i;

	num = NULL;
	num = ft_strdup("0123456789");
	i = 0;
	while (num[i] != '\0')
	{
		if (stresp[0] == num[i])
		{
			to_free(num);
			return (1);
		}
		i++;
	}
	to_free(num);
	return (0);
}
