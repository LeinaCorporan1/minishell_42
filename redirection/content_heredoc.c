/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 01:09:21 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/22 15:44:19 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**init_content(char *limiter)
{
	char	**content;

	content = NULL;
	content = ft_calloc(sizeof(char *), 3);
	if (quotes_identi(limiter[0]))
		content[0] = remove_quotes(limiter, quotes_identi(limiter[0]), 0);
	else
		content[0] = ft_strdup(limiter);
	return (content);
}

char	*found_content(char *buf, char *limiter, char *found, t_mini *mini)
{
	int		quotes;
	char	*var;

	var = NULL;
	quotes = quotes_identi(limiter[0]);
	if (quotes > 0)
		found = ft_strdup(buf);
	else
		found = checker_varia(buf, var, mini, 0);
	return (found);
}
