/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 04:39:32 by cmassavi          #+#    #+#             */
/*   Updated: 2023/03/15 10:45:29 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ret;

void	end_mini(t_mini *mini, char *buf)
{
	if (mini->heredoc_text != NULL)
		free(mini->heredoc_text);
	mini->tab_env = ft_free_dbl(mini->tab_env);
	free_lst(&mini->cmd);
	if (buf)
		free (buf);
	free_lst_env(mini->lst_env);
	free_lst_env_export(mini->lst_env_export);
}

void	ft_prompt(t_mini *mini)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_ret = 0;
	if (mini->quotes && !mini->quotes->splited)
		mini->quotes->splited = ft_strdup(" ");
	init_cmd(&mini->cmd, mini->quotes);
	free_quotes(&mini->quotes);
	if (nbr_cmd(mini->cmd) > 1)
		multi_exec(mini, mini->cmd);
	else
	{
		init_redirect(&mini->cmd->redirect);
		mini->cmd->cmd = ft_redirect(mini->cmd, &mini->cmd->redirect, mini);
		if (g_ret != 1 && mini->cmd->cmd != NULL
			&& !check_builtins(mini, mini->cmd->cmd, mini->cmd))
			exec(&mini->cmd->redirect, mini);
	}
	mini->cmd = free_lst(&mini->cmd);
	if (mini->heredoc_text)
		ft_free_heredoc(mini->heredoc_text);
}

int	exeption(char *buf)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(buf, ":"))
	{
		g_ret = 0;
		return (1);
	}
	if (!ft_strcmp(buf, "!"))
	{
		g_ret = 1;
		return (1);
	}
	while (buf[ret] == ' ')
		ret ++;
	if (ret == ft_strlen(buf))
	{
		g_ret = 0;
		return (1);
	}
	return (0);
}

void	else_main(t_mini *mini, char *buf)
{
	init_prompt(mini);
	checker_quotes(buf, &mini->quotes, mini);
	if (mini->quotes != NULL)
		ft_prompt(mini);
	else
		g_ret = 2;
}

int	main(int ac, char **av, char **env)
{
	char	*buf;
	t_mini	mini;

	(void)av;
	if (!isatty(0) || !isatty(1) || !isatty(2) || ac != 1)
		return (0);
	init_main(&mini, env);
	while (1)
	{
		mini.cmd = NULL;
		mini.heredoc_text = NULL;
		buf = NULL;
		buf = readline("Minishell > ");
		if (buf == NULL)
			return (free_ctrl_d(&mini, buf), 0);
		if (buf && ft_strlen(buf))
			add_history(buf);
		if (!buf[0] || exeption(buf) || checker_syntax(buf, &mini) != 0)
			free (buf);
		else
			else_main(&mini, buf);
	}
	return (end_mini(&mini, buf), g_ret);
}
