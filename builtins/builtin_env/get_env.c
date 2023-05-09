/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:36:15 by massavie          #+#    #+#             */
/*   Updated: 2023/01/11 11:28:35 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*since_car_one(char *buf, char c)
{
	int		i;
	int		x;
	char	*str;

	i = 0;
	x = count_since_car(buf, c);
	str = malloc(sizeof(char) * (x + 1));
	if (!str)
		return (buf);
	x = 0;
	while (buf[i] != '\0' && buf[i] != c)
		i++;
	if (buf[i] == '\0')
		return (ft_str_ndup(buf));
	else
		i++;
	while (buf[i] != '\0')
		str[x++] = buf[i++];
	str[x] = '\0';
	return (str);
}

void	print_export(char *buf, int fd)
{
	char	*untilg;
	char	*since;

	untilg = until_equal(buf);
	since = since_car_one(buf, '=');
	ft_putstr_fd("export ", fd);
	ft_putstr_fd(untilg, fd);
	ft_putstr_fd("=", fd);
	ft_putstr_fd("\"", fd);
	ft_putstr_fd(since, fd);
	ft_putstr_fd("\"", fd);
	ft_putstr_fd("\n", fd);
	free (untilg);
	free (since);
}

int	printlst_envxport(t_exp *lst_env_export, int fd)
{
	t_element_export	*actual_export;

	if (lst_env_export == NULL)
		return (0);
	actual_export = lst_env_export -> next;
	while (actual_export != NULL)
	{
		if (position_equal(actual_export->str) != -1)
		{
			print_export(actual_export->str, fd);
		}
		else
		{
			ft_putstr_fd("export ", fd);
			ft_putstr_fd(actual_export -> str, fd);
			ft_putstr_fd("\n", fd);
		}
		actual_export = actual_export -> next;
	}
	return (1);
}

char	**tab_env_aftxp(t_lst_env *lst_env)
{
	t_element	*actual;
	char		**tab_env;
	int			count_element;
	int			i;

	i = 0;
	count_element = count_lst_env(lst_env);
	if (lst_env == NULL || count_element <= 0)
		return (NULL);
	tab_env = ft_calloc(sizeof(char *), count_element + 1);
	if (!tab_env)
		return (NULL);
	actual = lst_env -> next;
	while (actual != NULL)
	{
		tab_env[i] = ft_str_ndup(actual -> str);
		actual = actual -> next;
		i++;
	}
	tab_env[i] = NULL;
	return (tab_env);
}

void	get_env(t_lst_env *lst_env, char **env)
{
	int	i;

	i = 0;
	if (env[i] != NULL)
	{
		intro(lst_env, env[i]);
		i++;
	}
	while (env[i] != NULL)
	{
		introback(lst_env, env[i]);
		i++;
	}
}
