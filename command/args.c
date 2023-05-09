/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:30:42 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 15:12:16 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_cmd_quotes(t_quote *quotes, char **tab, int y)
{
	int	i;
	int	space;
	int	cmd_quote;
	int	quote;

	i = 0;
	space = 0;
	quote = 0;
	cmd_quote = quotes->found_quotes;
	if (quotes->splited == NULL)
		return (4);
	while (quotes && quotes->splited[i])
	{
		if (quotes->splited[i] == ' ')
			space = 1;
		if (quotes->splited[i] == '\'' || quotes->splited[i] == '"')
			quote = 1;
		i++;
	}
	if (quotes && quotes->found_quotes && space == 0 && quote == 0 && y != 2)
		cmd_quote = 0;
	if (tab != NULL && tab[1] && ft_atoi(tab[1]) != 0)
		cmd_quote = 1;
	return (cmd_quote);
}

char	**join_tmp(char	**tmp, char **tab, int y, t_quote *quotes)
{
	char	*q;

	q = ft_strdup("'");
	if (ft_atoi(tmp[1]) && y == 2 && quotes->splited != NULL && tmp[0] == NULL)
	{
		if (ft_atoi(tmp[1]) == 2)
		{
			free (q);
			q = ft_strdup("\"");
		}
		tmp[0] = ft_strdup(q);
	}
	if (tab == NULL && quotes->splited != NULL)
		tmp[0] = ft_strjoin(tmp[0], quotes->splited);
	else if (quotes->splited != NULL && tab && tab[0])
		tmp[0] = ft_strjoin(ft_strdup(tab[0]), quotes->splited);
	else if (tab != NULL && tab[0] != NULL)
		tmp[0] = ft_strdup(tab[0]);
	if (ft_atoi(tmp[1]) && y == 2 && quotes->splited != NULL)
		tmp[0] = ft_strjoin(tmp[0], q);
	free(q);
	return (tmp);
}

char	**cmd_args_init(char **tab, t_quote *quotes, int y)
{
	char	**tmp;

	tmp = ft_calloc(sizeof(char *), 3);
	tmp[1] = ft_itoa(init_cmd_quotes(quotes, tab, y));
	if (ft_atoi(tmp[1]) < 4)
		tmp = join_tmp(tmp, tab, y, quotes);
	if (quotes->space && quotes->next && quotes->next->splited != NULL
		&& quotes->splited != NULL && ((y == 1
				&& (!ft_strncmp(quotes->splited, "echo", (int)ft_strlen("echo"))
					|| !ft_strncmp(quotes->splited,
						"-n", (int)ft_strlen("-n")))
				&& ft_atoi(tmp[1]) == 0 && quotes->next)
			|| (y == 2
				&& ((ft_strncmp(quotes->next->splited, "|", ft_strlen("|")))
					|| (!ft_strncmp(quotes->next->splited, "|", ft_strlen("|"))
						&& quotes->next->found_quotes != 0)))))
		tmp[0] = ft_strjoin(tmp[0], " ");
	ft_free_dbl(tab);
	return (tmp);
}

char	***init_args(char ***args, t_quote *quotes, int c, int special)
{
	char	*argv;
	char	**to_add;
	char	***to_join;

	to_add = NULL;
	to_join = NULL;
	argv = NULL;
	if (quotes && quotes->splited != NULL)
	{
		if (c == 2)
		{
			to_add = cmd_args_init(to_add, quotes, 2);
			if (special == 34)
			{
				argv = ft_strjoin(argv, " ");
				argv = ft_strjoin(argv, to_add[0]);
				free (to_add[0]);
				to_add[0] = ft_strdup_free(argv);
			}
		}
	}
	to_join = ft_join_tr(args, to_add);
	if (to_add != NULL)
		ft_free_dbl(to_add);
	return (to_join);
}
