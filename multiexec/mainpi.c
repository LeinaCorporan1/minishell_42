/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainpi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:11:44 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 17:35:13 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_muex(int frk, char *path, char **args)
{
	if (args != NULL)
		args = free_tab(args);
	if (path)
		free (path);
	return (frk);
}

void	mufail(char **args)
{
	if (args)
	{
		ft_error ("command not found\n");
		ft_error ("bash : ");
		ft_error (args[0]);
		ft_error (" : command not found\n");
		g_ret = 127;
	}
}

void	ft_waitpid(int *pids, int argnum)
{
	int	x;

	x = -1;
	while (++x < argnum)
	{
		if (pids[x] > 0)
			waitpid(pids[x], &g_ret, 0);
	}
	g_ret = WEXITSTATUS(g_ret);
}

void	sure_close(int pipefd[][2], int argnum)
{
	int	x;

	x = -1;
	while (++x < argnum)
	{
		if (pipefd[x][0] >= 3)
			close (pipefd[x][0]);
		if (pipefd[x][1] >= 3)
			close (pipefd[x][1]);
	}
}

int	multi_exec(t_mini *mini, t_cmd *cmd)
{
	int		pipefd[1024][2];
	int		pids[1024];
	int		x;
	int		argnum;

	argnum = nbr_cmd(cmd);
	x = -1;
	while (++x < argnum)
	{
		pipe(pipefd[x]);
		if (x == 0)
			pids[x] = muexec(cmd, pipefd, x, mini);
		else if (x == argnum - 1)
			pids[x] = mu_exec_last(cmd, pipefd, x, mini);
		else
			pids[x] = mu_mi_exec(cmd, pipefd, x, mini);
		cmd = cmd -> next;
	}
	ft_waitpid(pids, argnum);
	sure_close(pipefd, argnum);
	return (g_ret);
}
