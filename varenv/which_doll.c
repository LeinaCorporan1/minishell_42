/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_doll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:39:09 by massavie          #+#    #+#             */
/*   Updated: 2023/02/22 19:46:17 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**str_split_doll(char *str, char sep, t_mini *mini)
{
	char	**tabl;
	char	*str_sp;
	char	*until_sp;
	int		i;
	int		count;

	count = count_sep(str, sep);
	tabl = malloc(sizeof(char *) * (count + 2));
	tabl[count + 1] = NULL;
	i = -1;
	while (++i <= count)
	{
		str_sp = ft_split_one(str, '$');
		until_sp = until_space(str_sp);
		tabl[i] = which_split_doll(i, str_sp, until_sp, mini);
		str = str + ft_strlen(str_sp) + 1;
		freestrsplitdoll(str_sp, until_sp);
	}
	return (tabl);
}

char	*strsplitdoll2(char *buf, char *stresp, char *until_sp, int car)
{
	char	*sinceca;
	char	*sincep;

	sinceca = since_car(stresp, car);
	sincep = since_sp(stresp);
	if (car != 0)
		buf = ft_strjoin(buf, sinceca);
	else
		buf = ft_strjoin(buf, sincep + (int)ft_strlen(until_sp));
	free (sinceca);
	free (sincep);
	return (buf);
}

char	*strsplitdoll3(char *stresp)
{
	char	*buf;
	char	*since;
	int		car;

	car = check_car_spe_doll(stresp);
	since = since_car(stresp, car);
	buf = ft_str_ndup(since);
	free (since);
	return (buf);
}

char	*strsplitdoll4(char *until_sp, char *stresp, t_lst_env *lst_env)
{
	int		car;
	int		lenequal;
	char	*buf;

	car = 0;
	lenequal = 0;
	car = check_car_spe_doll(until_sp);
	lenequal = len_car(find_occ_one(lst_env, until_sp), '=');
	buf = ft_str_ndup(find_occ_one(lst_env, until_sp) + lenequal);
	buf = strsplitdoll2(buf, stresp, until_sp, car);
	return (buf);
}

char	*which_split_doll(int i, char *stresp, char *until_sp, t_mini *mini)
{
	char	*buf;
	char	*doll;
	char	*echo_doll;
	char	*point;

	point = ft_strdup("?");
	if (i == 0)
		buf = ft_str_ndup(stresp);
	else if (ft_strcmp(until_sp, "\0") == 0)
	{
		doll = ft_str_ndup("$");
		buf = ft_strjoin(doll, stresp);
	}
	else if (check_num_first(stresp) == 1)
		buf = ft_str_ndup(stresp + 1);
	else if (ft_strncmp(stresp, point, 1) == 0)
	{
		echo_doll = echodoll();
		buf = ft_strjoin(echo_doll, stresp + 1);
	}
	else if (findfirstoccurence(mini->lst_env, until_sp) != -1 && i != 0)
		buf = strsplitdoll4(until_sp, stresp, mini->lst_env);
	else
		buf = strsplitdoll3(stresp);
	return (to_free(point), buf);
}
