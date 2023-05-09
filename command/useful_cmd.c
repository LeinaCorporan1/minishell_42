/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:28:42 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 10:02:46 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_lst(t_cmd *lst)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!lst && lst == NULL)
	{
		return (0);
	}
	if (lst && lst->cmd)
			count = 1;
	if (lst->args)
	{
		while (lst->args && lst->args[i])
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	nbr_cmd(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd == NULL)
		return (i);
	if (cmd -> next == NULL)
		return (i);
	while (cmd -> next != NULL)
	{
		cmd = cmd -> next;
		i++;
	}
	return (i);
}

t_cmd	*free_lst(t_cmd **cmd)
{
	t_cmd	*del;
	t_cmd	*stack;

	del = *cmd;
	while (del && del != NULL)
	{
		stack = del -> next;
		if (del->cmd != NULL)
		{
			free(del->cmd);
		}
		if (del->args != NULL)
			ft_free_tr(del->args);
		if (del != NULL)
			free(del);
		del = stack;
	}
	del = NULL;
	return (del);
}
