/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:04:07 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/23 08:55:02 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
{
	if (g_ret == 981)
	{
		rl_on_new_line();
		write (1, "\n", 1);
		rl_replace_line("", 1);
		g_ret = 555;
		return ;
	}
	if (sig == 2)
	{
		rl_on_new_line();
		write (1, "\n", 1);
		rl_replace_line("", 1);
		rl_redisplay();
		g_ret = 130;
	}
}

void	handle_sigint_here(int sig)
{
	char	newline[2];

	(void)sig;
	newline[0] = '\n';
	newline[1] = '\0';
	rl_replace_line("", 0);
	rl_on_new_line();
	if (ioctl(STDIN_FILENO, TIOCSTI, newline) == -1)
		return ;
	g_ret = 130;
}

void	free_ctrl_d(t_mini *mini, char *buf)
{
	if (mini->heredoc_text)
		ft_free_heredoc(mini->heredoc_text);
	if (mini->tab_env)
		mini->tab_env = ft_free_dbl(mini->tab_env);
	if (mini->cmd)
		free_lst(&mini->cmd);
	if (buf)
		free (buf);
	if (mini->lst_env)
		free_lst_env(mini->lst_env);
	if (mini->lst_env_export)
		free_lst_env_export(mini->lst_env_export);
	ft_putstr_fd("\nexit\n", 2);
}

void	free_ctrl_d_copy(t_mini *mini, char *buf)
{
	if (mini->heredoc_text)
		ft_free_heredoc(mini->heredoc_text);
	if (mini->tab_env)
		mini->tab_env = ft_free_dbl(mini->tab_env);
	if (mini->cmd)
		free_lst(&mini->cmd);
	if (buf)
		free (buf);
	if (mini->lst_env)
		free_lst_env(mini->lst_env);
	if (mini->lst_env_export)
		free_lst_env_export(mini->lst_env_export);
}

void	signal_exec(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
