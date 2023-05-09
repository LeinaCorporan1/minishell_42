/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:05:10 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 16:19:33 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split_syntax(char *buf)
{
	int		i;
	int		y;
	char	**tmp;
	int		pos;

	tmp = ft_calloc(sizeof(char *), count_split_syntax(buf) + 1);
	y = 0;
	pos = 0;
	i = 0;
	while (pos < (int)ft_strlen(buf) && buf[pos] != '\0')
	{
		y = quote_valid(buf + pos);
		if (y == -1)
			y = (int)ft_strlen(buf);
		if (y == -2)
			return (tmp);
		while (y != (int)ft_strlen(buf) && buf[pos + y] && (y == 0
				|| (y == 1 && buf[pos + y] != ' ') || buf[pos + y] == ' '))
			y++;
		tmp[i] = ft_strndup(buf + pos, y);
		pos = pos + y;
		i++;
	}
	return (tmp);
}

int	special_syntax(char **tab, int i)
{
	char	*str_sp;
	char	*s_sp;

	if (tab [i + 1])
	{
		str_sp = until_space(tab[i]);
		s_sp = until_space(tab[i + 1]);
		if (!ft_strcmp(str_sp, "<"))
		{
			if (!ft_strcmp(s_sp, ">"))
			{
				free(str_sp);
				free(s_sp);
				return (0);
			}
			else
				return (1);
		}
		return (1);
	}
	return (0);
}

int	checker_syntax_utils(char **tab, char **token, int i)
{
	if (tab[i] && checker_token(tab[i], token, -2) && (!tab[i + 1]
			|| checker_token(tab[i + 1], token, 0)))
	{
		if (special_syntax(tab, i))
			print_token_error(1, tab[i + 1]);
		else
			print_token_error(0, tab[i]);
		if (tab)
			ft_free_dbl(tab);
		ft_free_dbl(token);
		return (2);
	}
	else if (tab[i] && checker_token(tab[i], token, 2) && (i - 1 < 0
			|| !tab[i + 1] || (i - 1 >= 0
				&& checker_token(tab[i - 1], token, 0))))
	{
		print_token_error(1, tab[i]);
		if (tab)
			ft_free_dbl(tab);
		ft_free_dbl(token);
		return (2);
	}
	return (0);
}

int	checker_found_heredoc(char **tab, char **token, int i, t_mini *mini)
{
	char	*here;
	char	*remove_1;
	int		record_g_ret;

	here = NULL;
	if (tab[i][0] == '<' && tab[i][1] == '<' && tab[i + 1] &&
		!checker_token(tab[i + 1], token, 0))
	{
		here = since_sp(tab[i + 1]);
		record_g_ret = g_ret;
		remove_1 = remove_quotes_echo(here, 1);
		free(here);
		here = remove_quotes_echo(remove_1, 2);
		free(remove_1);
		ft_heredoc(ft_cut(here, ' '), mini);
		if (g_ret != 130)
			g_ret = record_g_ret;
		if (here)
			free (here);
	}
	return (0);
}

int	checker_syntax(char *buf, t_mini *mini)
{
	char	**token;
	char	**tab;
	int		i;

	token = ft_split("> < |", ' ');
	buf = added_space_token(token, buf);
	tab = NULL;
	tab = ft_split_syntax(buf);
	i = -1;
	free (buf);
	while (tab && tab[++i] != NULL)
	{
		if (checker_found_heredoc(tab, token, i, mini) == 1)
		{
			i++;
		}
		if (checker_syntax_utils(tab, token, i) == 2)
			return (2);
	}
	if (tab)
		ft_free_dbl(tab);
	if (token)
		ft_free_dbl(token);
	return (0);
}
