/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:10:46 by cmassavi          #+#    #+#             */
/*   Updated: 2023/01/11 04:24:16 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	cmd_pos(char **tmp, int i)
{
	if (redir(tmp[i][0]) && tmp[i + 1] && tmp[i + 2]
		&& !redir(tmp[i + 1][0]) && !redir(tmp[i + 2][0]))
		return (i + 2);
	else if (!redir(tmp[0][0]))
		return (0);
	else
		return (-1);
}

void	exec_std(t_redirect *redirect)
{
	if (redirect -> stdin >= 0)
		close (redirect -> stdin);
	if (redirect -> stdout >= 0)
		close (redirect -> stdout);
}

char	*added_space(char *argv, int quotes)
{
	char	*space_added;
	int		y;

	y = 0;
	space_added = NULL;
	if (quotes != 0)
		space_added = ft_strdup(argv);
	while (quotes == 0 && argv[y])
	{
		space_added = ft_strjoin_char(space_added, argv[y]);
		if (((argv[y] == '>' || argv[y] == '<')
				&& (argv[y + 1] && argv[y + 1] != argv[y]
					&& argv[y + 1] != ' '))
			|| (argv[y] != '>' && argv[y] != '<' && argv[y] != ' '
				&& (argv[y + 1] && (argv[y + 1] == '>' || argv[y + 1] == '<'))))
			space_added = ft_strjoin_char(space_added, ' ');
		y++;
	}
	free (argv);
	return (space_added);
}
