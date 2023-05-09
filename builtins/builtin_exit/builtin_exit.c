/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leina <leina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:36:27 by massavie          #+#    #+#             */
/*   Updated: 2023/02/22 21:51:34 by leina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_numeric(char **str, t_mini *mini)
{
	int	lenstr;
	int	c;
	int	i;

	i = 0;
	lenstr = (int)ft_strlen(str[1]);
	while (i < lenstr)
	{
		c = str[1][i];
		if (((c < 48 || c > 57) && (c != '+' && c != '-'
					&& c != 34 && c != 39)) || (count_moreless(str[1]) == 2))
		{
			ft_error("Error : numeric argument required\n");
			g_ret = 2;
			free_tab(str);
			free_ctrl_d(mini, NULL);
			exit (2);
		}
		i++;
	}
	return (0);
}

int	count_moreless(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+' || str[i] == '-')
			count++;
		i++;
	}
	if (count > 1)
		return (2);
	else
		return (0);
}

int	check_number(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] < 48 || buf[i] > 57)
		{
			ft_error ("Numeric argument required\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	base_exit(char **arg, t_mini *mini)
{
	long long	n;

	parse_quote(arg[1]);
	ft_numeric(arg, mini);
	n = ft_atoi_exit(arg[1]);
	ft_atoi_unsigned(arg[1]);
	if (n >= 0 && n < 256)
	{
		if (arg)
			free_tab(arg);
		g_ret = n;
		free_ctrl_d(mini, NULL);
		exit (n);
	}
	if (n < 0)
		exit_neg(n, arg, mini);
	else if (n > 255 && n <= 9223372036854775807)
		exit_mod(n, arg, mini);
	else
		exit_arg_inc(arg, mini);
}

long long	builtin_exit(char *str, char **arg, t_mini *mini)
{
	if (!str)
		return (0);
	if (ft_strcmp(arg[0], "exit") != 0)
		return (-1);
	if (arg[1] == NULL)
		exit_no_arg(arg, mini);
	else if (arg[1] != NULL && arg[2] == NULL)
		base_exit(arg, mini);
	if (arg[2] != NULL)
		return (exit_tmarg(arg, mini));
	return (0);
}
