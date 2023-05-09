/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chloe <chloe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:17:07 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/21 23:56:18 by chloe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exp	*initialisation_export(void)
{
	t_exp					*lst_env;
	t_element_export		*element;

	lst_env = malloc(sizeof(*lst_env));
	element = malloc(sizeof(*element));
	if (lst_env == NULL || element == NULL)
		exit (EXIT_FAILURE);
	element -> str = ft_strdup("NULL");
	element -> next = NULL;
	lst_env -> next = element;
	return (lst_env);
}

t_exp	*init_introbackexpsort(t_exp *lst_env, char *string)
{
	t_element_export	*new;

	if (lst_env == NULL)
		return (NULL);
	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->str = ft_strdup(string);
	new->next = NULL;
	if (lst_env->next == NULL)
	{
		lst_env->next = new;
		return (lst_env);
	}
	return (lst_env);
}

t_exp	*introbackexpsort(t_exp *lst_env, char *string)
{
	t_element_export	*new;
	t_element_export	*temp;

	new = malloc(sizeof(*new));
	if (lst_env == NULL || !new)
		return (NULL);
	new->str = ft_strdup(string);
	new->next = NULL;
	if (lst_env->next == NULL)
		return (init_introbackexpsort(lst_env, string));
	temp = lst_env->next;
	if (sort_buf(temp->str, string) == 0 || sort_buf(temp->str, string) == 1)
	{
		new->next = temp;
		lst_env->next = new;
	}
	else
	{
		while (temp -> next != NULL && sort_buf(temp->next->str, string) == -1)
			temp = temp -> next;
		new -> next = temp -> next;
		temp -> next = new;
	}
	return (lst_env);
}

t_exp	*intro_export(t_exp *lst_env, char *string)
{
	t_element_export	*new;

	new = malloc(sizeof(*new));
	if (lst_env == NULL || new == NULL)
		return (NULL);
	new -> str = ft_strdup(string);
	new -> next = lst_env -> next;
	lst_env -> next = new;
	return (lst_env);
}
