/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mu_mi_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:38:08 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 16:41:31 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_close_mi(int pipefd[][2], int arg, t_cmd *cmd)
{
	ft_dup(&cmd->redirect);
	if (cmd->redirect.stdin == -2 && cmd->redirect.heredoc == -2)
	{
		dup2(pipefd[arg - 1][0], STDIN);
		close (pipefd[arg - 1][0]);
	}
	if (cmd->redirect.stdout == -2)
	{
		dup2(pipefd[arg][1], STDOUT);
		close (pipefd[arg][1]);
	}
	close(pipefd[arg][0]);
	close(pipefd[arg - 1][1]);
	if (!cmd->cmd)
	{
		exec_std(&cmd -> redirect);
		sure_close(pipefd, arg);
	}
}

void	close_mi(int pipefd[][2], int arg)
{
	close(pipefd[arg - 1][0]);
	close(pipefd[arg][1]);
}

void	exit_mu_fail(t_mini *mini, char **args, char *path, int i)
{
	if (mini->heredoc_text)
		ft_free_heredoc(mini->heredoc_text);
	free_ctrl_d_copy(mini, NULL);
	if (path)
		free (path);
	if (args)
		free_tab(args);
	exit(i);
}

int	mu_mi_exec(t_cmd *cmd, int pipefd[][2], int arg, t_mini *mini)
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
		dup_close_mi(pipefd, arg, cmd);
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
		close_mi(pipefd, arg);
	init_signal();
	return (exec_std(&cmd->redirect), free_muex(frk, pa.path, pa.args));
}
