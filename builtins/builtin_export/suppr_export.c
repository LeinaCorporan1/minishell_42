/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 00:34:29 by massavie          #+#    #+#             */
/*   Updated: 2023/02/20 14:17:46 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	suppression_export(t_exp *lst_env)
{
	t_element_export	*to_free;

	if (lst_env == NULL)
		return (0);
	if (lst_env -> next != NULL)
	{
		if (lst_env->next->str)
			free(lst_env->next->str);
		to_free = lst_env -> next;
		lst_env -> next = lst_env -> next -> next;
		free (to_free);
	}
	return (1);
}

int	free_lst_env_export(t_exp *lst_env)
{
	t_element_export	*to_free;

	if (lst_env == NULL)
		return (0);
	while (lst_env -> next != NULL)
	{
		if (lst_env->next->str)
			free(lst_env->next->str);
		to_free = lst_env -> next;
		lst_env -> next = lst_env -> next -> next;
		free(to_free);
	}
	free (lst_env);
	return (1);
}
