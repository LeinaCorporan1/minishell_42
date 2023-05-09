/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:38:11 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 16:39:35 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_quote	*qt_joined(char *str, t_quote *quotes)
{
	t_quote	*tmp;
	int		fnd;
	int		i;

	i = -1;
	fnd = -1;
	tmp = quotes;
	tmp->splited = NULL;
	tmp->found_quotes = 0;
	while (str[++i] != '\0')
	{
		if (str[i] != '\0' && (str[i] == 39 || str[i] == '"') && fnd == -1)
		{
			fnd = i;
			if (str[i] == '"')
				tmp->found_quotes = 2;
			else
				tmp->found_quotes = 1;
		}
		if (str[i] != '\0' && ((fnd >= 0 && str[fnd] != str[i]) || fnd == -1))
			tmp->splited = ft_strjoin_char(tmp->splited, str[i]);
		if (str[i] != '\0' && fnd >= 0 && i != fnd && str[fnd] == str[i])
		fnd = -1;
	}
	return (free (str), tmp);
}

t_quote	*quote_empty(t_quote *stack, char *str, int end)
{
	t_quote	*add;
	char	*buf;

	buf = NULL;
	add = (t_quote *)malloc(sizeof(t_quote));
	if (end == 0 || (end == 1 && (!redir(str[end - 1]) && str[end] != ' ')))
		end++;
	if (end < ft_strlen(str) && ((str[end] && str[end] == ' ')
			|| (quotes_identi(str[end])
				&& str[end + 1] && str[end + 1] == ' ')))
		add->space = 1;
	else
		add->space = 0;
	buf = ft_strndup(str, end);
	add = qt_joined(buf, add);
	add->next = NULL;
	stack = add;
	return (stack);
}

t_quote	*quote_back(t_quote *lst, char *str, int end)
{
	t_quote	*add;
	t_quote	*temp;
	char	*buf;

	buf = NULL;
	add = (t_quote *)malloc(sizeof(t_quote));
	if (end == 0 || (end == 1 && (!redir(str[end - 1]) && str[end] != ' ')))
		end++;
	if (end < ft_strlen(str) && ((str[end] && str[end] == ' ')
			|| (quotes_identi(str[end]) && str[end + 1]
				&& str[end + 1] == ' ')))
		add->space = 1;
	else
		add->space = 0;
	add->next = NULL;
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	buf = ft_strndup(str, end);
	add = qt_joined(buf, add);
	temp->next = add;
	return (lst);
}

int	to_add(int i, char *str, int begin, t_quote *tmp)
{
	i = quote_valid(str + begin);
	if (i == -1)
	i = (int)ft_strlen(str);
	if (i == -2)
	{
		ft_putstr_fd("bash: unclosed quotes\n", 2);
		free (str);
		free_quotes(&tmp);
		return (-1);
	}
	if (ft_strlen(str) > begin + i && str[begin + i] != '\0'
		&& str[begin + i] != ' '
		&& str[begin + i + 1] == '|')
		i++;
	if (begin + i < (int)ft_strlen(str) && redir(str[begin + i]))
		i++;
	return (i);
}

void	checker_quotes(char *buf, t_quote **quotes, t_mini *mini)
{
	int		i;
	int		begin;
	char	*str;
	t_quote	*tmp;

	tmp = *quotes;
	str = NULL;
	str = checker_varia(since_sp(buf), str, mini, 0);
	begin = 0;
	i = 0;
	while (i < (int)ft_strlen(str) && str[i] != '\0')
	{
		i = to_add(i, str, begin, tmp);
		if (i == -1)
			return ;
		if (begin == 0)
			tmp = quote_empty(tmp, str + begin, i);
		else
			tmp = quote_back(tmp, str + begin, i);
		begin = incrementation(i, begin, 1, str);
		i = incrementation(begin + i, begin, 2, str);
		begin = i;
	}
	free (str);
	*quotes = tmp;
}
