/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:03:03 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/24 13:21:13 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_redirect(t_redirect *redirect)
{
	redirect->infile = NULL;
	redirect->outfile = NULL;
	redirect->stdin = -2;
	redirect->stdout = -2;
	redirect->heredoc = -2;
	redirect->content_here = NULL;
}

char	*open_write(int i, char *to_write, char *in)
{
	int		openi;
	char	*doc;
	char	*num;

	num = ft_itoa(i);
	doc = ft_strjoin(ft_strjoin(ft_strdup("/tmp/"), in), num);
	openi = open(doc, O_CREAT | O_TRUNC | O_RDWR, 0000644);
	write(openi, to_write, ft_strlen(to_write));
	close (openi);
	free (num);
	return (doc);
}

int	init_content_here(t_redirect *redirect, char *in, t_mini *mini)
{
	long long int	i;
	char			*doc;

	i = -1;
	doc = NULL;
	while (mini->heredoc_text != NULL && mini->heredoc_text[++i])
	{
		if (ft_strncmp(mini->heredoc_text[i][0], in, (int)ft_strlen(in)) == 0
		&& (int)ft_strlen(mini->heredoc_text[i][0]) == (int)ft_strlen(in))
		{
			doc = open_write(i, mini->heredoc_text[i][1], in);
			redirect->heredoc = open(doc, O_RDONLY);
			if (redirect->heredoc == -1)
				return (to_free(doc), -1);
			return (to_free(doc), 0);
		}
		doc = str_null(doc);
	}
	return (to_free(doc), 0);
}

char	*init_args_redir(t_cmd *cmd, t_redirect *red, t_mini *mini)
{
	int		i;
	char	***args;

	args = NULL;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		if (redir(cmd->args[i][0][0]))
		{
			redir_valid(cmd->args, red, mini, i);
			if (g_ret == 1 || !cmd->args[i + 1])
				break ;
			i++;
		}
		else if (cmd->args[i] != NULL)
			args = ft_join_tr(args, cmd->args[i]);
		i++;
	}
	ft_free_tr(cmd->args);
	cmd->args = ft_join_tr(args, NULL);
	return (NULL);
}

char	**init_cmd_redir(t_cmd *cmd)
{
	char	*argv;
	char	**tmp;

	argv = NULL;
	argv = added_space(cmd->cmd, cmd->cmd_quotes);
	if (cmd->cmd_quotes == 0)
		tmp = ft_split(argv, ' ');
	else
		tmp = ft_split(argv, '\0');
	free(argv);
	return (tmp);
}
