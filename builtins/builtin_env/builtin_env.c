/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:36:06 by massavie          #+#    #+#             */
/*   Updated: 2023/02/23 00:08:33 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_lst_env(t_lst_env *lst_env)
{
	int			i;
	t_element	*actual;

	i = 0;
	if (lst_env == NULL)
		return (0);
	actual = lst_env -> next;
	while (actual != NULL)
	{
		i++;
		actual = actual -> next;
	}
	return (i);
}

int	printlist(t_lst_env *lst_env, int fd)
{
	t_element	*actual;

	if (lst_env == NULL)
		return (0);
	actual = lst_env -> next;
	while (actual != NULL)
	{
		ft_putstr_fd(actual->str, fd);
		ft_putstr_fd("\n", fd);
		actual = actual -> next;
	}
	return (0);
}

int	builtin_env2(t_mini *mini, char **bufsplit, int i)
{
	if (ft_strcmp(bufsplit[i], "ls") == 0)
		return (exec(&mini->cmd->redirect, mini));
	return (env_perm_such(i, bufsplit));
}

int	builtin_env(t_mini *mini, int fd, char **bufsplit)
{
	int	i;

	i = 1;
	if (bufsplit[1] == NULL)
		return (printlist(mini->lst_env, fd));
	else if (ft_strcmp(bufsplit[1], "ls") == 0 && bufsplit[2] == NULL)
		return (exec(&mini->cmd->redirect, mini));
	else if (bufsplit[1][0] == '-' && i == 0)
		return (env_ivld_opt(bufsplit[1]));
	else if (ft_strcmp(bufsplit[1], "env") == 0)
	{
		while (bufsplit[i] != NULL && ft_strcmp(bufsplit[i], "env") == 0)
			i++;
		if (i == count_tab(bufsplit))
			return (printlist(mini->lst_env, fd));
		if (bufsplit != NULL)
			return (builtin_env2(mini, bufsplit, i));
	}
	else if (ft_strncmp(bufsplit[1], "./", 2) == 0)
		return (env_perm_such(1, bufsplit));
	else
		return (env_cmd_not_found(bufsplit));
	return (0);
}
