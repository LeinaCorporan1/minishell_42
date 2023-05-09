/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findocc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:41:02 by massavie          #+#    #+#             */
/*   Updated: 2023/02/21 11:03:55 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_sim(t_mini *mini, char **bufsplit, int i, char *until)
{
	supp_occ(mini->lst_env, until);
	supp_occ_export(mini->lst_env_export, until);
	introbackexpsort(mini->lst_env_export, bufsplit[i]);
	introback(mini->lst_env, bufsplit[i]);
}

int	findoccurence(t_lst_env *lst_env, char *string)
{
	int			i;
	t_element	*actual;

	i = 0;
	if (lst_env == NULL)
		return (-1);
	actual = lst_env -> next;
	while (actual != NULL)
	{
		if (ft_strcmp(actual -> str, string) == 0)
			return (i);
		actual = actual -> next;
		i++;
	}
	return (-1);
}

int	findfirstoccurence(t_lst_env *lst_env, char *string)
{
	int			i;
	char		*until;
	t_element	*actual;

	i = 0;
	if (lst_env == NULL || string == NULL)
		return (-1);
	actual = lst_env -> next;
	while (actual != NULL)
	{
		until = ft_cut(actual -> str, '=');
		if (ft_strcmp(until, string) == 0)
			return (free(until), i);
		actual = actual -> next;
		i++;
		free (until);
	}
	return (-1);
}

int	findfirstoccurence_exp(t_exp *lst_env, char *string)
{
	int					i;
	char				*until;
	t_element_export	*actual;

	i = 0;
	if (lst_env == NULL || string == NULL)
		return (-1);
	actual = lst_env -> next;
	while (actual != NULL)
	{
		until = ft_cut(actual -> str, '=');
		if (ft_strcmp(until, string) == 0)
			return (free(until), i);
		actual = actual -> next;
		i++;
		free (until);
	}
	return (-1);
}

char	*find_occ_one(t_lst_env *lst_env, char *string)
{
	int			i;
	char		*until;
	t_element	*actual;

	i = 0;
	if (lst_env == NULL)
		return (NULL);
	actual = lst_env -> next;
	while (actual != NULL)
	{
		until = until_equal(actual -> str);
		if (ft_strcmp(until, string) == 0)
			return (free(until), actual->str);
		actual = actual -> next;
		i++;
		free (until);
	}
	return (NULL);
}
