/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:07:01 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 22:55:45 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_pwd(int fd, t_mini *mini)
{
	char	*path;
	char	*exp;
	char	**split_exp;
	char	*exp_pwd;

	path = NULL;
	exp = NULL;
	split_exp = NULL;
	path = malloc(sizeof(char) * (4096 + 1));
	if (!path)
		return (0);
	if (getcwd(path, 4097) == NULL)
	{
		if (path)
			to_free (path);
		return (0);
	}
	exp_pwd = ft_strdup("export PWD=");
	exp = ft_strjoin(exp_pwd, path);
	split_exp = ft_split(exp, ' ');
	builtin_export(NULL, mini, fd, split_exp);
	free_tab(split_exp);
	to_free (path);
	to_free (exp);
	return (0);
}

int	get_old_pwd(int fd, t_mini *mini)
{
	char	*path;
	char	*exp;
	char	**split_exp;
	char	*exp_pwd;

	path = NULL;
	exp = NULL;
	split_exp = NULL;
	path = malloc(sizeof(char) * (4096 + 1));
	if (!path)
		return (0);
	if (getcwd(path, 4097) == NULL)
	{
		if (path)
			to_free(path);
		return (0);
	}
	exp_pwd = ft_strdup("export OLDPWD=");
	exp = ft_strjoin(exp_pwd, path);
	split_exp = ft_split(exp, ' ');
	builtin_export(NULL, mini, fd, split_exp);
	free_tab(split_exp);
	free (path);
	to_free(exp);
	return (0);
}
