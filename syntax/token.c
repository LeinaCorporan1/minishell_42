/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:03:17 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 19:46:01 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token_error(int error, char *token)
{
	int	i;

	i = -1;
	ft_putstr_fd("bash: syntax error near unexpected token '", 2);
	if (error == 0)
		ft_putstr_fd("newline", 2);
	while (error == 1 && token[++i] && token[i] != ' ' && i < 2)
		write(2, &token[i], 1);
	ft_putstr_fd("'\n", 2);
	g_ret = 2;
}

int	checker_token(char *tab, char **token, int wich)
{
	int	i;

	if (wich == 2)
		i = 2;
	if (wich == 0 || wich == -2)
		i = 0;
	while (token[i] && token[i] != NULL)
	{
		if (wich == -2 && i == 2)
			return (0);
		if (token[i] != NULL && token[i][0] == tab[0])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*added_space_token_utils(char *token, char *argv, int i, char *tmp)
{
	int	c;

	c = i + 1;
	while (argv[c] == token[0] && c <= i + 1)
	{
		tmp = ft_strjoin_char(tmp, argv[c]);
		c++;
	}
	i = c - 1;
		tmp = ft_strjoin_char(tmp, ' ');
	return (tmp);
}

int	c_result(char **token, char *argv, int i, int y)
{
	int	c;

	c = 0;
	c = i + 1;
	while (argv[c] == token[y][0] && c <= i + 1)
		c++;
	return (c);
}

char	*added_space_token(char **token, char *argv)
{
	int		i;
	int		y;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (argv[++i])
	{
		y = -1;
		tmp = ft_strjoin_char(tmp, argv[i]);
		while (token[++y])
		{
			if (argv[i] == token[y][0])
			{
				tmp = added_space_token_utils(token[y], argv, i, tmp);
				i = c_result(token, argv, i, y) - 1;
			}
			else if (argv[i] != token[y][0] && argv[i + 1]
			&& argv[i + 1] == token[y][0])
					tmp = ft_strjoin_char(tmp, ' ');
		}
	}
	return (tmp);
}
