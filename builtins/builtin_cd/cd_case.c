/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_case.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:07:29 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 23:38:59 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd_ivld_opt(char **bufsplit)
{
	ft_error ("env : ");
	ft_error (bufsplit[1]);
	ft_error (" : option invalid\n");
	g_ret = 2;
	return (2);
}

int	cd_too_mnyarg(void)
{
	ft_error ("Error : Too many arguments\n");
	g_ret = 1;
	return (1);
}

int	cd_cdt(char **split_buf, t_mini *mini, int fd)
{
	char	*buf_home;

	buf_home = NULL;
	if (ft_strcmp(split_buf[1], "--") == 0 && split_buf[2] == NULL)
	{
		buf_home = varia("$HOME", mini);
		if (chdir(buf_home) != 0)
		{
			ft_error ("bash : cd : home set nu\n");
			g_ret = 1;
		}
		if (buf_home)
			to_free (buf_home);
		return (0);
	}
	else if (split_buf[1][1] == '\0')
	{
		builtin_pwd(fd);
		return (0);
	}
	return (0);
}

int	cd_old_pwd(t_mini *mini, int fd)
{
	char	*old_pwd;

	old_pwd = NULL;
	old_pwd = varia("$OLDPWD", mini);
	get_old_pwd(fd, mini);
	if (chdir(old_pwd) != 0)
		not_directory(old_pwd);
	get_pwd(fd, mini);
	if (old_pwd)
		to_free (old_pwd);
	return (0);
}

int	cd_home(t_mini *mini, int fd)
{
	char	*buf_home;

	buf_home = NULL;
	buf_home = varia("$HOME", mini);
	if (ft_strlen(buf_home) < 1)
	{
		ft_error("bash : cd: HOME not set\n");
		if (buf_home)
			to_free(buf_home);
		g_ret = 1;
		return (1);
	}
	get_old_pwd(fd, mini);
	chdir(buf_home);
	get_pwd(fd, mini);
	free (buf_home);
	return (0);
}
