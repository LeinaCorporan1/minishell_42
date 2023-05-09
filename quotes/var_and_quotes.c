/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_and_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:43:41 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 17:37:49 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_dollar(char *str)
{
	int	i;
	int	valid;

	valid = 1;
	i = 0;
	while (str[i] && valid > 0)
	{
		if (str[i] == '"' || str[i] == 39)
		{
			if (i == 1)
				return (i * -1);
			else
				return (i);
		}
		i++;
	}
	if (valid == 1)
		valid = i;
	return (valid);
}

char	*strdup_varia(char *str, char *to_return, t_mini *mini)
{
	char	*var;
	char	*tmp;

	var = NULL;
	tmp = NULL;
	if (valid_dollar(str) > 0)
	{
		tmp = ft_strndup(str, valid_dollar(str));
		var = varia(tmp, mini);
		to_return = ft_strjoin(to_return, var);
		free (var);
		free (tmp);
		tmp = NULL;
		var = NULL;
	}
	return (to_return);
}

int	i_dollar(char *str, int i)
{
	if (valid_dollar(str + i) < 0)
		i = i + (valid_dollar(str + i) * -1);
	else
		i = i + valid_dollar(str + i);
	return (i);
}

int	checker_varia_condi(char *str, int quotes, int i)
{
	if (quotes == 2 && str[i] == '$' && i + 1 < ft_strlen(str)
		&& str[i + 1] == '"' && i + 2 < ft_strlen(str) && str[i + 2] == '"')
		return (0);
	if ((quotes == 0 || quotes == 2) && str[i] == '$'
		&& i + 1 < (int)ft_strlen(str) && str[i + 1] != ' '
		&& str[i + 1] != '"')
		return (1);
	return (0);
}

char	*checker_varia(char *str, char *to_return, t_mini *mini, int quotes)
{
	int		i;

	i = -1;
	to_return = NULL;
	mini->tok = 0;
	while (str && str[++i])
	{
		if (quotes == 0)
		{
			quotes = quotes_identi(str[i]);
			if (quotes > 0)
				mini->tok = i;
		}
		if (checker_varia_condi(str, quotes, i) == 1)
		{
			to_return = strdup_varia(str + i, to_return, mini);
			i = i_dollar(str, i);
			if (i == (int)ft_strlen(str))
				break ;
		}
		to_return = ft_strjoin_char(to_return, str[i]);
		if (mini->tok != i && str[i] == str[mini->tok])
			quotes = 0;
	}
	return (free(str), to_return);
}
