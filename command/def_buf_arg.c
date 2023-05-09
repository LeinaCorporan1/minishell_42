/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_buf_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:27:44 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 08:55:27 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*if_def_buf_arg(char *buf)
{
	char	*tmp;
	char	*str;

	str = NULL;
	tmp = since_sp(buf);
	str = ft_cut(tmp, ' ');
	if (tmp != NULL)
		tmp = str_null(tmp);
	return (str);
}

char	*def(char *buf, int flag)
{
	char	*str;

	str = NULL;
	if (flag == 0)
		str = if_def_buf_arg(buf);
	else
		str = remove_quotes(buf, flag, 0);
	return (str);
}

char	**def_buf_arg(t_cmd *lst, char **bufarg)
{
	int		i;
	int		x;
	int		j;

	i = -1;
	x = -1;
	j = 1;
	if (lst == NULL || !lst->cmd)
		return (NULL);
	bufarg = calloc(sizeof(char *), count_lst(lst) + 1);
	bufarg[0] = ft_strdup(lst -> cmd);
	while (lst != NULL && ++x <= 0)
	{
		if (lst->args != NULL)
		{
			while (lst->args[++i])
				bufarg[j++] = def(lst->args[i][0], ft_atoi(lst->args[i][1]));
		}
		lst = lst->next;
	}
	bufarg[j] = NULL;
	return (bufarg);
}
