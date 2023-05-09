/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppocc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:44:25 by massavie          #+#    #+#             */
/*   Updated: 2023/02/22 16:21:15 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	supp_occ_null(t_lst_env *lst_env, int i)
{
	if (lst_env == NULL)
		return (0);
	if (i == 0)
		return (suppression(lst_env), 1);
	return (0);
}

int	supp_occ_scd(t_lst_env *lst_env, int i)
{
	t_element	*to_free;
	t_element	*actual;

	actual = lst_env -> next;
	if (actual != NULL && i == 0)
		return (suppression(lst_env), 1);
	while (actual != NULL)
	{
		if (--i == 0)
		{
			if (actual -> next -> str)
				free (actual -> next -> str);
			to_free = actual -> next;
			if (actual -> next -> next == NULL)
				actual -> next = NULL;
			else
			{
				actual -> next = actual -> next -> next;
				actual = actual -> next -> next;
			}
			return (free(to_free), 1);
		}
		actual = actual -> next;
	}
	return (0);
}

int	supp_occ(t_lst_env *lst_env, char *string)
{
	int			i;

	i = findfirstoccurence(lst_env, string);
	if (lst_env == NULL || i == -1)
		return (supp_occ_null(lst_env, i));
	return (supp_occ_scd(lst_env, i));
}
