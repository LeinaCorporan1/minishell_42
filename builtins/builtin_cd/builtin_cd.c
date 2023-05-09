/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:35:28 by massavie          #+#    #+#             */
/*   Updated: 2023/02/22 23:39:13 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_cd(t_mini *mini, int fd, char **split)
{
	if ((split[1] == NULL) || (split[1][0] == '~'
		&& split[1][1] == '\0' && split[2] == NULL))
		return (cd_home(mini, fd));
	if (split[1][0] == '-')
	{
		if (split[1][1] == '\0')
			return (cd_old_pwd(mini, fd));
		if (split[1][1] != '-')
		{
			g_ret = 1;
			return (ft_error("cd : usage : invalid option\n"), 1);
		}
		if ((ft_strcmp(split[1], "--") == 0 && split[2] == NULL)
			|| split[1][1] == '\0')
			return (cd_cdt(split, mini, fd));
		else if (split[1][2] == '-')
			return (cd_ivld_opt(split));
	}
	if (split[2] != NULL)
		return (cd_too_mnyarg());
	diff_cd(split[1], mini, fd);
	return (0);
}
