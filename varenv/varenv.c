/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:38:56 by massavie          #+#    #+#             */
/*   Updated: 2023/02/22 18:09:49 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*varia(char *buf, t_mini *mini)
{
	char	**strsplit;
	char	*str;

	if (check_doll(buf) == 0)
		return (buf);
	strsplit = str_split_doll(buf, '$', mini);
	str = string_var(strsplit);
	strsplit = free_tab(strsplit);
	return (str);
}
