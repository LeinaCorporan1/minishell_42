/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:36:32 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/21 11:09:16 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_opt_ivld(char **bufsplit, char *until, int i)
{
	int	c;

	c = bufsplit[i][1];
	ft_error ("bash : export : -");
	write (2, &c, 1);
	ft_error (" : option invalid\n");
	g_ret = 2;
	free (until);
	return (2);
}

void	export_no_sim(t_mini *mini, char **bufsplit, int i)
{
	introbackexpsort(mini->lst_env_export, bufsplit[i]);
	introback(mini->lst_env, bufsplit[i]);
}

void	supp_one_occ(t_lst_env *lst_env, t_exp *exp, char *string)
{
	supp_occ(lst_env, string);
	supp_occ_export(exp, string);
}

void	export_no_equal(char **bufsplit, int i, t_mini *mini, char *until)
{
	if (findfirstoccurence_exp(mini->lst_env_export, until) == -1)
	{
		if (bufsplit[i] != NULL)
			introbackexpsort(mini->lst_env_export, bufsplit[i]);
	}
	else if (findfirstoccurence_exp(mini->lst_env_export, until) != 1)
	{
		supp_one_occ(mini->lst_env, mini->lst_env_export, until);
		if (bufsplit[i] != NULL)
			introbackexpsort(mini->lst_env_export, bufsplit[i]);
	}
	else
	{
	}
}

void	export_no_occ(t_mini *mini, char **bufsplit, int i, char *until)
{
	if (findfirstoccurence_exp(mini->lst_env_export, until) != -1)
		export_sim(mini, bufsplit, i, until);
	else
		export_no_sim(mini, bufsplit, i);
}
