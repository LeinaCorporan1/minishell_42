/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:36:17 by massavie          #+#    #+#             */
/*   Updated: 2023/02/23 00:00:03 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//ok

int	env_perm_such(int i, char **bufsplit)
{
	if (bufsplit[i][0] == '.' && bufsplit[i][1] == '/')
		return (env_perm(bufsplit[i]));
	else if (ft_strcmp(bufsplit[i], "ls") != 0)
		return (env_no_such(bufsplit[i]));
	return (0);
}

int	env_cmd_not_found(char **bufsplit)
{
	int	i;

	i = 1;
	ft_error ("Error : env : ");
	while (bufsplit[i] != NULL)
	{
		ft_error (bufsplit[i++]);
		ft_error (" ");
	}
	ft_error (": no such file directory of file\n");
	g_ret = 127;
	return (127);
}

int	env_ivld_opt(char *buf)
{
	ft_error ("env : ");
	ft_error (buf);
	ft_error (" : option invalid\n");
	g_ret = 125;
	return (125);
}

int	env_perm(char *buf)
{
	ft_error ("Error : env : ");
	ft_error (buf);
	ft_error (": Permission denied\n");
	g_ret = 126;
	return (126);
}

int	env_no_such(char *buf)
{
	ft_error ("Error : env : ");
	ft_error (buf);
	ft_error (": no such file directory of file\n");
	g_ret = 127;
	return (127);
}
