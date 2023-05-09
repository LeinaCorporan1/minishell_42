/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:29 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 16:39:07 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*add_empty(t_cmd *stack, char **str, char ***arg, t_quote *quotes)
{
	t_cmd	*add;

	add = (t_cmd *)malloc(sizeof(t_cmd));
	add->cmd = NULL;
	add->args = NULL;
	if (str)
	{
		add->cmd = ft_strdup(str[0]);
		add->cmd_quotes = ft_atoi(str[1]);
		ft_free_dbl(str);
	}
	if (arg)
	{
		add->args = init_args(arg, quotes, -1, 0);
	}
	add->next = NULL;
	stack = add;
	return (stack);
}

t_cmd	*add_back(t_cmd *lst, char **str, char ***arg, t_quote *quotes)
{
	t_cmd	*add;
	t_cmd	*temp;

	add = (t_cmd *)malloc(sizeof(t_cmd));
	add->cmd = NULL;
	add->args = NULL;
	if (str)
	{
		add->cmd = ft_strdup(str[0]);
		add->cmd_quotes = ft_atoi(str[1]);
	}
	if (arg)
	{
		add->args = init_args(arg, quotes, -1, 0);
	}
	ft_free_dbl(str);
	add->next = NULL;
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = add;
	return (lst);
}

t_cmd	*adding_cmd(t_quote *quotes, t_cmd *tmp, char **cmd_split, char ***arg)
{
	if (quotes == NULL || quotes->splited == NULL
		|| (quotes->splited != NULL
			&& !ft_strncmp(quotes->splited, "|", (int)ft_strlen("|"))
			&& quotes->found_quotes == 0))
	{
		if (tmp == NULL)
			return (add_empty(tmp, cmd_split, arg, quotes));
		else
			return (add_back(tmp, cmd_split, arg, quotes));
	}
	return (NULL);
}

int	init_condition(t_quote *quotes, int special, char **cmd_split, int y)
{
	if (y == 1)
	{
		if (quotes != NULL && (quotes->splited == NULL
				|| (quotes->splited != NULL
					&& ((!ft_strncmp(quotes->splited, "|", ft_strlen("|"))
							&& quotes->found_quotes != 0)
						|| ft_strncmp(quotes->splited, "|", ft_strlen("|"))))))
			return (1);
	}
	if (y == 2)
	{
		if (quotes->splited != NULL && ((special <= -1 && cmd_split != NULL)
				|| (cmd_split == NULL && special <= 0)))
			return (1);
	}
	return (0);
}

void	init_cmd(t_cmd **cmd, t_quote *quotes)
{
	int		special;
	char	**cmd_split;
	char	***arg;
	t_cmd	*tmp;

	tmp = *cmd;
	special = 0;
	while (quotes != NULL)
	{
		cmd_split = NULL;
		arg = NULL;
		while (init_condition(quotes, special, cmd_split, 1) == 1)
		{
			special = special_cmd(quotes, special, cmd_split);
			if (init_condition(quotes, special, cmd_split, 2) == 1)
				cmd_split = cmd_args_init(cmd_split, quotes, 1);
			else if (quotes->splited != NULL)
				arg = init_args(arg, quotes, 2, special);
			quotes = quotes->next;
		}
		tmp = adding_cmd(quotes, tmp, cmd_split, arg);
		if (quotes != NULL)
			quotes = quotes->next;
	}
	*cmd = tmp;
}
