/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:38:29 by massavie          #+#    #+#             */
/*   Updated: 2023/03/14 14:03:26 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_stdin(t_redirect *redirect, char *tmp, char *in, t_mini *mini)
{
	if (tmp[1] == '<')
		return (init_content_here(redirect, in, mini));
	redirect->stdin = open(in, O_RDONLY);
	if (redirect->stdin == -1 || redirect->heredoc == -1)
		return (msg_error_files(2, in), -1);
	return (0);
}

int	redir_open(t_redirect *redirect, char *tmp, char *in, t_mini *mini)
{
	if (tmp[0] == '>' && !redir(in[0]))
	{
		if (redirect->stdout != -2)
			close(redirect->stdout);
		if (tmp[1] && tmp[1] == '>')
			redirect->stdout = open(in, O_CREAT | O_APPEND | O_RDWR, 0000644);
		else
			redirect->stdout = open(in, O_CREAT | O_TRUNC | O_RDWR, 0000644);
		if (redirect->stdout == -1)
			return (msg_error_files(2, in), -1);
	}
	if (tmp[0] == '<' && !redir(in[0]))
		return (redir_stdin(redirect, tmp, in, mini));
	return (0);
}

int	msg_error_files(int types, char *in)
{
	if (types == 3)
	{
		g_ret = 1;
		return (ft_putstr_fd("ambiguous redirect\n", 2), 1);
	}
	ft_putstr_fd(in, 2);
	if (types == 2)
		return (ft_putstr_fd(": open failed\n", 2), 1);
	return (0);
}

char	*redir_valid(char ***args, t_redirect *redirect, t_mini *mini, int i)
{
	char	*argv;

	argv = NULL;
	if (args[i] && !args[i + 1])
		return (msg_error_files(3, args[i][0]), NULL);
	if (ft_atoi(args[i + 1][1]) > 0)
		args[i + 1][0] = remove_quotes(args[i + 1][0],
				ft_atoi(args[i + 1][1]), 1);
	else
	{
		argv = since_sp(args[i + 1][0]);
		free (args[i + 1][0]);
		args[i + 1][0] = ft_cut(argv, ' ');
	}
	if (redir_open(redirect, args[i][0], args[i + 1][0], mini) == -1)
	{
		g_ret = 1;
		return (to_free(argv), NULL);
	}
	if (argv != NULL)
		free (argv);
	return (NULL);
}

char	*ft_redirect(t_cmd *cmd, t_redirect *redirect, t_mini *mini)
{
	char	*cmd_redir;
	char	**tmp;

	cmd_redir = NULL;
	if (cmd->cmd != NULL)
	{
		tmp = init_cmd_redir(cmd);
		cmd_redir = in_herdoc(cmd_redir, redirect, tmp, mini);
		if (cmd_redir == NULL)
		{
			if (redirect->stdout == -1 || redirect->stdin == -1)
				g_ret = 1;
			return (ft_free_dbl(tmp), NULL);
		}
		ft_free_dbl(tmp);
	}
	if (cmd->args)
	{
		init_args_redir(cmd, redirect, mini);
		if (redirect->stdout == -1 || redirect->stdin == -1)
			g_ret = 1;
	}
	return (cmd_redir);
}
