/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:21 by massavie          #+#    #+#             */
/*   Updated: 2023/02/22 14:35:36 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	option_pwd(char *buf)
{
	if (buf[0] == '-')
	{
		if (buf[1] == '-')
		{
			ft_error ("pwd : -- : invalid option\n");
			g_ret = 2;
			return (2);
		}
		if (buf[1] != '-')
		{
			ft_error ("pwd : ");
			ft_error (buf);
			ft_error (" : invalid option\n");
			g_ret = 2;
			return (2);
		}
	}
	return (0);
}

int	builtin_pwd(int fd)
{
	char	*path;

	path = NULL;
	path = malloc(sizeof(char) * (4096 + 1));
	if (path == NULL)
		return (-1);
	if (getcwd(path, 4097) == NULL)
	{
		ft_error ("Error\n");
		if (path)
			free(path);
		return (0);
	}
	ft_putstr_fd(path, fd);
	ft_putstr_fd("\n", fd);
	if (path)
		free (path);
	return (0);
}
