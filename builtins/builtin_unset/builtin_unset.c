/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:08 by massavie          #+#    #+#             */
/*   Updated: 2023/02/22 19:58:23 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset_event(int i, char **bufsplit)
{
	ft_error ("unset : ");
	ft_error (bufsplit[i]);
	ft_error (" : event not found\n");
	g_ret = 0;
	return (0);
}

int	unset_not_val(int i, char **bufsplit)
{
	ft_error ("unset : ");
	ft_error (bufsplit[i]);
	ft_error (": not a valider caracter\n");
	g_ret = 1;
	return (1);
}

int	builtin_unset_one(char **bufsplit)
{
	if (!bufsplit)
		return (0);
	if (bufsplit[1] == NULL)
	{
		return (0);
	}
	else if (bufsplit[1][0] == '-')
	{
		ft_error ("unset : ");
		ft_error (bufsplit[1]);
		ft_error (" : Invalid option\n");
		g_ret = 2;
		return (2);
	}
	return (0);
}

int	find_first_occ_exp(t_exp *lst_env, char *string)
{
	int					i;
	char				*until;
	t_element_export	*actual;

	i = 0;
	if (lst_env == NULL)
		return (-1);
	actual = lst_env -> next;
	while (actual != NULL)
	{
		until = ft_cut(actual -> str, '=');
		if (ft_strcmp(until, string) == 0)
		{
			if (until)
				free (until);
			return (i);
		}
		if (until)
			free (until);
		actual = actual -> next;
		i++;
	}
	return (-1);
}

int	builtin_unset(t_lst_env *lst_env, t_exp *exp, char **bufsplit)
{
	int	i;
	int	car;

	i = 0;
	car = -1;
	if (!bufsplit || bufsplit[1] == NULL || bufsplit[1][0] == '-')
		return (builtin_unset_one(bufsplit));
	while (bufsplit[++i])
	{
		car = check_car_spe_doll(bufsplit[i]);
		if (car != 0)
		{
			if (car == 33)
				return (unset_event(i, bufsplit));
			else
				return (unset_not_val(i, bufsplit));
		}
		supp_occ(lst_env, bufsplit[i]);
		supp_occ_export(exp, bufsplit[i]);
	}
	return (1);
}
