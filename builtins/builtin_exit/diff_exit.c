/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:36:49 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 16:21:06 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_neg(long long n, char **arg, t_mini *mini)
{
	long long	div;
	long long	tot;

	div = 0;
	tot = 0;
	n *= -1;
	div = n / 256;
	div *= 256;
	n -= div;
	tot = 256 - n;
	if (arg)
		free_tab(arg);
	g_ret = tot;
	free_ctrl_d(mini, NULL);
	exit (tot);
}

int	exit_tmarg(char **arg, t_mini *mini)
{
	ft_numeric(arg, mini);
	ft_error("bash: line 0: exit: too many arguments\n");
	g_ret = 1;
	return (1);
}

void	exit_arg_inc(char **arg, t_mini *mini)
{
	ft_error ("Argument incorrect\n");
	if (arg)
		free_tab(arg);
	g_ret = 255;
	free_ctrl_d(mini, NULL);
	exit(255);
}

void	exit_mod(long long n, char **arg, t_mini *mini)
{
	if (arg)
		free_tab(arg);
	g_ret = n % 256;
	free_ctrl_d(mini, NULL);
	exit (n % 256);
}

void	exit_no_arg(char **arg, t_mini *mini)
{
	if (arg)
		free_tab(arg);
	g_ret = 0;
	free_ctrl_d(mini, NULL);
	exit (0);
}
