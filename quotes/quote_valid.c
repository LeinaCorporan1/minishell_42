/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:45:23 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 15:35:46 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_identi(char c)
{
	if (c == '"')
		return (2);
	if (c == 39)
		return (1);
	return (0);
}

int	incrementation(int i, int begin, int wich, char *str)
{
	if (wich == 1)
	{
		if (str[begin] == '|')
			begin++;
		return (begin);
	}
	if (wich == 2)
	{
		while (i < (int)ft_strlen(str) && str[i] && str[i] == ' ')
			i++;
		return (i);
	}
	return (0);
}

int	quote_valid_utils(char *to_check, int i, int quotes, int wich)
{
	if (wich == 1)
	{
		if (quotes < 0 && !quotes_identi(to_check[i])
			&& (((to_check[i + 1] == '|' || to_check[i] == '|')
					|| ((redir(to_check[i]) && i == 0))) && i >= 0))
		{
			if ((redir(to_check[i]) && i == 0) && (redir(to_check[i + 1])
					|| to_check[i + 1] == '|'))
				i = i + 1;
			return (i);
		}
		if (quotes == -1 && i > 0 && (to_check[i] == ' '
				|| (to_check[i - 1] == '|' || to_check[i] == '|')))
			return (i);
	}
	if (wich != 1 && to_check[i + 1] && to_check[i + 1] == ' '
		&& (!quotes_identi(to_check[i + 1]) || (to_check[i + 1] == 39
				&& to_check[quotes] != to_check[i + 1])
			|| (to_check[i + 1] == '"'
				&& to_check[quotes] != to_check[i + 1])))
		return (i + 1);
	return (-1);
}

int	quotes_valid_quotes(char *to_check, int i, int quotes, int wich)
{
	if (wich == 1)
	{
		if ((to_check[i + 1] == 39 && to_check[quotes] == to_check[i + 1])
			|| (to_check[i + 1] == '"' && to_check[quotes] == to_check[i + 1]))
			quotes = -1;
		else
			quotes = -2;
	}
	else
	{
		if (to_check[i] && (to_check[i] == 39 || to_check[i] == '"')
			&& quotes == -1)
			quotes = i;
	}
	return (quotes);
}

int	quote_valid(char *to_check)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = -1;
	while (to_check[++i])
	{
		if (quote_valid_utils(to_check, i, quotes, 1) != -1)
			return (quote_valid_utils(to_check, i, quotes, 1));
		quotes = quotes_valid_quotes(to_check, i, quotes, 0);
		if (quotes == -2 && to_check[i] == ' ')
			return (i);
		if (i != quotes && quotes >= 0 && quotes < (int)ft_strlen(to_check)
			&& to_check[quotes] == to_check[i])
		{
			if (quote_valid_utils(to_check, i, quotes, 0) != -1)
				return (quote_valid_utils(to_check, i, quotes, 0));
			quotes = quotes_valid_quotes(to_check, i, quotes, 1);
		}
	}
	if (quotes >= 0)
		return (-2);
	return (-1);
}
