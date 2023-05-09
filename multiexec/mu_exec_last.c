/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mu_exec_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:38:02 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 16:41:34 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_close_last(int pipefd[][2], int arg, t_cmd *cmd)
{
	ft_dup(&cmd->redirect);
	if (cmd->redirect.stdin == -2 && cmd->redirect.heredoc == -2)
	{
		dup2(pipefd[arg -1][0], STDIN);
		close (pipefd[arg - 1][0]);
	}
	close(pipefd[arg - 1][1]);
	close(pipefd[arg][1]);
	close(pipefd[arg][0]);
	if (!cmd->cmd)
	{
		exec_std(&cmd -> redirect);
		sure_close(pipefd, arg);
	}
}

int	mu_exec_last(t_cmd *cmd, int pipefd[][2], int arg, t_mini *mini)
{
	t_exec	pa;
	int		frk;

	init_pa(&pa, cmd, mini);
	ignore_signal();
	frk = fork();
	g_ret = 981;
	if (frk == 0)
	{
		signal_exec();
		dup_close_last(pipefd, arg, cmd);
		if (cmd->cmd == NULL)
			exit_mu_fail(mini, pa.args, pa.path, 1);
		if (!check_builtins(mini, cmd->cmd, cmd))
			if (!pa.path || execve(pa.path, pa.args, mini->tab_env) == -1)
				mufail(pa.args);
		exec_std(&cmd -> redirect);
		sure_close(pipefd, arg);
		exit_mu_fail(mini, pa.args, pa.path, g_ret);
	}
	else
		close (pipefd[arg - 1][0]);
	init_signal();
	return (exec_std(&cmd->redirect), free_muex(frk, pa.path, pa.args));
}
