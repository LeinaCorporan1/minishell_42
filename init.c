/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:50:32 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/24 16:27:35 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialisation_mini(t_mini *mini)
{
	g_ret = 0;
	mini->cmd = NULL;
	mini->quotes = NULL;
	mini->heredoc_text = NULL;
	mini->lst_env = initialisation();
	mini->lst_env_export = initialisation_export();
	suppression_export(mini->lst_env_export);
	mini->tab_env = NULL;
}

void	init_prompt(t_mini *mini)
{
	mini->tab_env = ft_free_dbl(mini->tab_env);
	mini->tab_env = tab_env_aftxp(mini->lst_env);
	mini->tok = 0;
}

void	init_main(t_mini *mini, char **env)
{
	initialisation_mini(mini);
	suppression(mini->lst_env);
	get_env(mini->lst_env, env);
	init_exp_sort(mini->lst_env, mini->lst_env_export);
	init_signal();
}

void	init_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
