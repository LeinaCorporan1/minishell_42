/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:24 by massavie          #+#    #+#             */
/*   Updated: 2023/02/23 08:51:42 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	which_builtins_sec(t_mini *mini, int ret, char *buf, char **bufargs)
{
	int	outfile;

	outfile = 1;
	if (mini->cmd->redirect.stdout != -2)
		outfile = mini->cmd->redirect.stdout;
	if (ret == 4)
		builtin_export(buf, mini, outfile, bufargs);
	if (ret == 5)
		builtin_unset(mini->lst_env, mini-> lst_env_export, bufargs);
	if (ret == 6)
		builtin_env(mini, outfile, bufargs);
	if (ret == 7)
		builtin_exit(buf, bufargs, mini);
	return (0);
}

int	which_builtins(t_mini *mini, int ret, char *buf, char **bufargs)
{
	int	outfile;

	outfile = 1;
	if (mini->cmd->redirect.stdout != -2)
		outfile = mini-> cmd -> redirect.stdout;
	if (ret == 2)
		builtin_cd(mini, outfile, bufargs);
	if (ret == 3)
	{
		if (bufargs[1] != NULL)
		{
			if (option_pwd(bufargs[1]) == 2)
				return (2);
		}
		builtin_pwd(outfile);
	}
	which_builtins_sec(mini, ret, buf, bufargs);
	return (0);
}

int	exec_which_bul(t_mini *mini, int i, char *buf, char **bufargs)
{
	which_builtins(mini, i, buf, bufargs);
	return (i);
}

char	**split_builtins(void)
{
	char	*str;
	char	**builts;

	str = ft_strdup("echo cd pwd export unset env exit");
	builts = ft_split(str, ' ');
	free (str);
	return (builts);
}

int	check_builtins(t_mini *mini, char *buf, t_cmd *cmd)
{
	char	**builts;
	int		i;
	char	**bufargs;

	builts = split_builtins();
	i = -1;
	bufargs = NULL;
	bufargs = def_buf_arg(cmd, bufargs);
	while (builts[++i] != NULL && bufargs != NULL)
	{
		if (ft_strncmp(builts[i], bufargs[0], (int)ft_strlen(builts[i])) == 0
			&& (!valid_echo(cmd, bufargs[0])))
		{
			ft_free_dbl(builts);
			exec_which_bul(mini, i + 1, buf, bufargs);
			if (bufargs != NULL)
				bufargs = free_tab(bufargs);
			return (1);
		}
	}
	bufargs = free_tab(bufargs);
	return (ft_free_dbl(builts), 0);
}
