/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:20:17 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 12:21:50 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lst_env	*initialisation(void)
{
	t_lst_env		*lst_env;
	t_element		*element;

	lst_env = malloc(sizeof(*lst_env));
	element = malloc(sizeof(*element));
	if (lst_env == NULL || element == NULL)
		exit (EXIT_FAILURE);
	element -> str = ft_strdup("NULL");
	element -> next = NULL;
	lst_env -> next = element;
	return (lst_env);
}

int	suppression(t_lst_env *lst_env)
{
	t_element	*to_free;

	if (lst_env == NULL)
		return (0);
	if (lst_env -> next != NULL)
	{
		if (lst_env->next->str)
			free(lst_env->next->str);
		to_free = lst_env -> next;
		if (lst_env->next->next)
			lst_env -> next = lst_env -> next -> next;
		else
			lst_env -> next = NULL;
		free (to_free);
	}
	return (1);
}

int	intro(t_lst_env *lst_env, char *string)
{
	t_element	*new;

	new = malloc(sizeof(*new));
	if (lst_env == NULL || new == NULL)
		return (0);
	new -> str = ft_strdup(string);
	new -> next = lst_env -> next;
	lst_env -> next = new;
	return (1);
}

t_lst_env	*introback(t_lst_env *lst_env, char *string)
{
	t_element	*new;
	t_element	*temp;

	if (lst_env == NULL)
		return (NULL);
	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(string);
	new->next = NULL;
	if (lst_env->next == NULL)
		lst_env->next = new;
	else
	{
		temp = lst_env->next;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (lst_env);
}

int	free_lst_env(t_lst_env *lst_env)
{
	t_element	*to_free;

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
