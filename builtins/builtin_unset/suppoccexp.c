/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppoccexp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:14 by massavie          #+#    #+#             */
/*   Updated: 2023/02/20 14:10:25 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	supp_occ_export2(t_exp *lst_env, int i)
{
	t_element_export	*to_free;
	t_element_export	*actual;

	actual = lst_env -> next;
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

int	supp_occ_export(t_exp *lst_env, char *string)
{
	int	i;

	i = find_first_occ_exp(lst_env, string);
	if (lst_env == NULL || i == 0)
		return (supp_exp_null(lst_env, i));
	return (supp_occ_export2(lst_env, i));
}

int	supp_exp_null(t_exp *lst_env, int i)
{
	if (lst_env == NULL)
		return (0);
	if (i == 0)
		return (suppression_export(lst_env), 1);
	return (0);
}

void	supp_all_occ(t_lst_env *lst_env, t_exp *exp, char **bufsplit)
{
	int	i;

	i = 1;
	while (bufsplit[i] != NULL)
	{
		supp_occ(lst_env, bufsplit[i]);
		supp_occ_export(exp, bufsplit[i]);
		i++;
	}
}
