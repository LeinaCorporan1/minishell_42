/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:38:23 by massavie          #+#    #+#             */
/*   Updated: 2023/01/11 02:09:32 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**join_tr_utils(char **to_join, char **add)
{
	to_join = ft_calloc(sizeof(char *), 3);
	to_join[0] = ft_strdup(add[0]);
	to_join[1] = ft_strdup(add[1]);
	to_join[2] = NULL;
	return (to_join);
}

char	***ft_join_tr(char ***args, char **add)
{
	int		i;
	int		y;
	char	***to_join;

	to_join = NULL;
	i = 0;
	y = ft_strlen_triple(args) + 1;
	if (add != NULL)
		y = y + 1;
	to_join = ft_calloc(sizeof(char **), y);
	if (!to_join)
		return (NULL);
	while (args != NULL && args[i] != NULL)
	{
		to_join[i] = join_tr_utils(to_join[i], args[i]);
		i++;
	}
	if (add != NULL)
	{
		to_join[i] = join_tr_utils(to_join[i], add);
		i++;
	}
	to_join[i] = NULL;
	return (ft_free_tr(args), to_join);
}

int	ft_strlen_triple(char ***tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

void	free_quotes(t_quote **quotes)
{
	t_quote	*del;
	t_quote	*stack;

	del = *quotes;
	while (del != NULL)
	{
		stack = del -> next;
		free(del->splited);
		free(del);
		del = stack;
	}
	del = NULL;
	*quotes = del;
}

char	*remove_quotes(char *input, int wich, int to_free)
{
	int		i;
	int		quotes;
	char	*to_return;

	i = 0;
	quotes = -1;
	to_return = NULL;
	while (input[i])
	{
		if (quotes > -1 && input[i] == input[quotes])
			quotes = -2;
		if (quotes != -1 && quotes != -2 && input[i] != input[quotes])
			to_return = ft_strjoin_char(to_return, input[i]);
		if (quotes_identi(input[i]) == wich && quotes == -1)
			quotes = i;
		i++;
	}
	if (to_free == 1)
		free (input);
	return (to_return);
}
