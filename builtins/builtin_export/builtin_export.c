/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:36:53 by massavie          #+#    #+#             */
/*   Updated: 2023/02/20 15:46:25 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	sort_buf(char *buf, char *str)
{
	int	i;

	i = 0;
	while (buf[i] != '\0' && str[i] != '\0')
	{
		if (buf[i] > str[i])
			return (1);
		else if (buf[i] == str[i])
			i++;
		else
			return (-1);
	}
	if (buf[i] == '\0')
		return (-1);
	if (str[i] == '\0')
		return (1);
	return (1);
}

void	init_exp_sort(t_lst_env *lst_env, t_exp *lst_env_export)
{
	t_element	*actual;
	int			i;

	i = 0;
	actual = lst_env -> next;
	while (actual != NULL)
	{
		if (i == 0)
			intro_export(lst_env_export, actual->str);
		else
			introbackexpsort(lst_env_export, actual -> str);
		i++;
		actual = actual -> next;
	}
}

void	if_export(t_mini *mini, char **bufsplit, int i, int occurence)
{
	char	*until;

	until = until_equal_no_car(bufsplit[i]);
	if (check_equal(bufsplit[i]) == -1)
	{
		if (findfirstoccurence(mini->lst_env, until) == -1)
			export_no_equal(bufsplit, i, mini, until);
	}
	else if (occurence == -1)
		export_no_occ(mini, bufsplit, i, until);
	else if (findfirstoccurence(mini->lst_env, until) != -1)
		supp_one_occ(mini->lst_env, mini->lst_env_export, until);
	free (until);
}

int	builtin_export(char *buf, t_mini *mini, int fd, char **bufsplit)
{
	char	*until;
	int		i;
	int		occurence;

	i = 0;
	if (bufsplit[1] == NULL)
		return (printlst_envxport(mini->lst_env_export, fd));
	while (bufsplit[++i] != NULL)
	{
		occurence = findoccurence(mini->lst_env, bufsplit[i]);
		until = until_equal_no_car(bufsplit[i]);
		if (bufsplit[i][0] == '-')
			return (export_opt_ivld(bufsplit, until, i));
		else if (bufsplit[i][0] == '=')
			return (nocar(buf, until, bufsplit[i]));
		else if (notvalid_car(until, bufsplit[i]) == 1)
			return (to_free(until));
		else
			if_export(mini, bufsplit, i, occurence);
		free (until);
	}
	return (1);
}
