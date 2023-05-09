/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmassavi <cmassavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 00:42:37 by cmassavi          #+#    #+#             */
/*   Updated: 2023/02/21 19:14:14 by cmassavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_ndup(char *str)
{
	char				*duped;
	unsigned int		i;

	i = 0;
	duped = malloc(sizeof(char) * ((int)ft_strlen(str) + 1));
	if (!duped)
		return (NULL);
	while (str[i] != '\0')
	{
		duped[i] = str[i];
		i++;
	}
	duped[i] = 0;
	return (duped);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	if (*s1 == '\0' && *s2 == '\0')
	{
		return (0);
	}
	else if (*s1 == '\0')
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}

char	*ft_strndup(char *src, int end)
{
	char	*dest;
	int		i;

	i = 0;
	if (end > (int)(int)ft_strlen(src))
		end = (int)(int)ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * end + 1);
	if (!dest)
		return (NULL);
	while (i < end && src[i])
	{
			dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup_free(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	dest = (char *)malloc(sizeof(const char) * ((int)ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	free (src);
	return (dest);
}

char	*ft_strjoin_char(char *s1, char c)
{
	int		i;
	char	*join;

	i = -1;
	if (!s1 || !s1[0])
	{
		s1 = malloc(sizeof(char) * 2);
		s1[0] = c;
		s1[1] = '\0';
		return (s1);
	}
	if (!s1)
		return (NULL);
	join = malloc(sizeof(char) * ((int)ft_strlen(s1) + 2));
	if (!join)
		return (NULL);
	while (s1 && s1[++i])
		join[i] = s1[i];
	join[i] = c;
	join[(int)ft_strlen(s1) + 1] = '\0';
	free(s1);
	return (join);
}
