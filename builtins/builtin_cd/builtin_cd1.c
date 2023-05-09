/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:35:44 by massavie          #+#    #+#             */
/*   Updated: 2023/02/21 23:55:25 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	file_noaccess(char *new_repo)
{
	if ((access(new_repo, F_OK) == 0) && (access(new_repo, R_OK) == 0))
		return (0);
	if (access(new_repo, F_OK))
		ft_error ("Error : The file does not exist\n");
	else if (access(new_repo, R_OK))
		ft_error ("Error: Permission denied\n");
	g_ret = 1;
	return (1);
}

int	not_directory(char *new_repo)
{
	ft_error ("bash : ");
	ft_error (new_repo);
	ft_error (" : Not a directory\n");
	g_ret = 1;
	return (1);
}

void	free_diff_cd(char *path, char *buf, char *buf2, char *oldpwd)
{
	if (path)
		free (path);
	if (buf)
		free (buf);
	if (buf2)
		free (buf2);
	if (oldpwd)
		free (oldpwd);
}

int	diff_cd(char *new_repo, t_mini *mini, int fd)
{
	if (access(new_repo, F_OK) || access(new_repo, R_OK))
		return (file_noaccess(new_repo));
	get_old_pwd(fd, mini);
	if (chdir(new_repo) != 0)
		return (not_directory(new_repo));
	else
		get_pwd(fd, mini);
	return (0);
}
