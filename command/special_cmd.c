/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:34 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 14:30:24 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	special_cmd_first(int prev, int space, char *split)
{
	int	special;

	special = 0;
	if (prev == 32)
		special = 34;
	if (space == 1 && split == NULL)
		special = 32;
	return (special);
}

int	special_cmd(t_quote *quotes, int prev_spe, char **cmd_split)
{
	int	special;

	special = special_cmd_first(prev_spe, quotes->space, quotes->splited);
	if (quotes->splited == NULL)
		return (special);
	if (prev_spe == 2)
		special = 3;
	if ((prev_spe == -1 || prev_spe == -2)
		&& !ft_strncmp(quotes->splited, "-n", 2)
		&& echo_newline_2(quotes->splited))
		special = 0 - 2;
	if (prev_spe > 0 && special != 34)
		special = prev_spe - 1;
	if (!quotes->found_quotes
		&& (!ft_strncmp(quotes->splited, ">", 1)
			|| !ft_strncmp(quotes->splited, "<", 1)))
	{
		special = 2;
		if (quotes->next != NULL && !ft_strncmp(quotes->next->splited, "|", 1))
		special --;
	}
	if (!ft_strncmp(quotes->splited, "echo", 4) && cmd_split == NULL)
		special = 0 - 1;
	return (special);
}
