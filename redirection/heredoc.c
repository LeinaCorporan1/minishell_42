/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leina <leina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:58:28 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 21:48:43 by leina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	valid_heredoc(char **content, char *limiter, char *buf, t_mini *mini)
{
	if (content != NULL && content[1] != NULL)
		mini->heredoc_text = ft_join_tr(mini->heredoc_text, content);
	ft_free_dbl(content);
	content = NULL;
	free(limiter);
	if (buf)
		free(buf);
}

int	ft_found_heredoc(char *buf, char *heredoc)
{
	int		i;
	int		y;
	int		quotes;
	char	*limit;

	i = 0;
	y = 0;
	quotes = quotes_identi(heredoc[0]);
	if (quotes > 0)
		limit = remove_quotes(heredoc, quotes, 0);
	else
		limit = ft_strdup(heredoc);
	if (buf && (int)ft_strlen(buf) != (int)ft_strlen(limit))
	{
		free(limit);
		return (0);
	}
	while (buf && buf[i] && limit[y])
	{
		if (buf[i] != limit[y])
			return (free(limit), 0);
		i++;
		y++;
	}
	return (free(limit), 1);
}

int	ft_heredoc(char *limiter, t_mini *mini)
{
	char	*buf;
	char	**content;
	char	*found;

	signal (SIGINT, SIG_DFL);
	found = NULL;
	content = init_content(limiter);
	signal(SIGINT, handle_sigint_here);
	while (g_ret != 130)
	{
		buf = readline("> ");
		if (g_ret == 130)
			return (ft_free_dbl(content), str_null(limiter), 0);
		if (ft_found_heredoc(buf, limiter))
			return (valid_heredoc(content, limiter, buf, mini), 1);
		found = found_content(buf, limiter, found, mini);
		content[1] = ft_strjoin(content[1], found);
		content[1] = ft_strjoin(content[1], "\n");
		found = str_null(found);
	}
	return (str_null(limiter), ft_free_dbl(content), 0);
}

char	*in_herdoc(char *cmd, t_redirect *red, char **tmp, t_mini *mini)
{
	int	i;
	int	y;

	i = -1;
	y = -1;
	while (tmp[++i] != NULL)
	{
		if (redir_open(red, tmp[i], tmp[i + 1], mini) == -1)
			return (NULL);
		if (cmd == NULL)
		{
			y = cmd_pos(tmp, i);
			if (y != -1)
			{
				cmd = ft_strdup(tmp[y]);
				while (tmp[++y] != NULL && !redir(tmp[y][0]))
				{
					cmd = ft_strjoin(cmd, " ");
					cmd = ft_strjoin(cmd, tmp[y]);
				}
			}
		}
	}
	return (cmd);
}

void	ft_free_heredoc(char ***heredoc_text)
{
	long long int	i;
	char			*doc;
	char			*num;

	i = 0;
	while (heredoc_text != NULL && heredoc_text[i])
	{
		num = ft_itoa(i);
		doc = ft_strjoin(ft_strjoin(ft_strdup("/tmp/"),
					heredoc_text[i][0]), num);
		unlink(doc);
		i++;
		free(doc);
		free(num);
	}
	ft_free_tr(heredoc_text);
}
