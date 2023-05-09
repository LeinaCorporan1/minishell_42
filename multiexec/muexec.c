/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   muexec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:55 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 16:41:21 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_execu(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_DFL);
}

void	dup_close_mu(int pipefd[][2], int arg, t_cmd *cmd)
{
	g_ret = 981;
	ft_dup(&cmd->redirect);
	if (cmd -> redirect.stdout == -2)
		dup2(pipefd[arg][1], STDOUT);
	close(pipefd[arg][0]);
	close(pipefd[arg][1]);
	if (!cmd->cmd)
	{
		exec_std(&cmd -> redirect);
		sure_close(pipefd, arg);
	}
}

void	init_pa(t_exec *pa, t_cmd *cmd, t_mini *mini)
{
	pa->args = NULL;
	pa->path = NULL;
	init_redirect(&cmd->redirect);
	cmd->cmd = ft_redirect(cmd, &cmd->redirect, mini);
	pa->args = def_buf_arg(cmd, pa->args);
	pa->path = ft_path(pa->args, mini->tab_env);
	if (pa->path == NULL && !cmd->cmd)
		pa->args = free_arg_path(pa->args, NULL);
}

int	muexec(t_cmd *cmd, int pipefd[][2], int arg, t_mini *mini)
{
	t_exec	pa;
	int		frk;

	init_pa(&pa, cmd, mini);
	ignore_signal();
	frk = fork();
	if (frk == 0)
	{
		signal_exec();
		dup_close_mu(pipefd, arg, cmd);
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
		close(pipefd[arg][1]);
	init_signal();
	return (exec_std(&cmd->redirect), free_muex(frk, pa.path, pa.args));
}
