/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:39 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 16:34:14 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_args(char **args)
{
	ft_error ("bash : ");
	ft_error (args[0]);
	ft_error (": command not found\n");
}

void	ft_dup(t_redirect *redirect)
{
	if (redirect->stdout != -2)
	{
		dup2(redirect->stdout, 1);
		unlink("re0");
	}
	if (redirect->heredoc != -2)
	{
		dup2(redirect->heredoc, 0);
	}
	else if (redirect->stdin != -2)
	{
		dup2(redirect->stdin, 0);
	}
}

void	exit_exec_err(t_mini *mini, char **args, char *path)
{
	ft_error_args(args);
	free_arg_path(args, path);
	free_ctrl_d_copy(mini, NULL);
	g_ret = 127;
	exit (127);
}

int	exec_return(int value)
{
	if (g_ret != 555)
		g_ret = WEXITSTATUS(value);
	else
		g_ret = 130;
	return (g_ret);
}

int	exec(t_redirect *redirect, t_mini *mini)
{
	char	*path;
	char	**args;
	int		frk;
	int		value;

	value = 0;
	path = NULL;
	args = NULL;
	args = def_buf_arg(mini->cmd, args);
	path = ft_path(args, mini->tab_env);
	ignore_signal();
	frk = fork();
	g_ret = 981;
	if (frk == 0)
	{
		signal_exec();
		ft_dup(redirect);
		if (!path || execve(path, args, mini->tab_env) == -1)
			exit_exec_err(mini, args, path);
	}
	waitpid (frk, &value, 0);
	g_ret = exec_return(value);
	init_signal();
	return (free_arg_path(args, path), exec_std(&mini->cmd->redirect), g_ret);
}
