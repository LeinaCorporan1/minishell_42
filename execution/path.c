/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:37:46 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 16:30:43 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_join(char *path, char *bin)
{
	char	*join;
	int		i;
	int		j;

	join = malloc(sizeof(char) * ((int)ft_strlen(path) \
					+ (int)ft_strlen(bin) + 2));
	if (!join)
	{
		free (join);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (path[i] != '\0')
	{
		join[i] = path[i];
		i++;
	}
	join[i] = '/';
	i++;
	while (bin[j] != '\0')
		join[i++] = bin[j++];
	join[i] = '\0';
	return (join);
}

char	*get_path_scd(char *cmd, char *s)
{
	char	*dir;
	char	*bin;
	int		lendir;

	while (s && new_colon(s) == 1)
	{
		dir = until_colon(s);
		lendir = (int)ft_strlen(dir);
		bin = path_join(dir, cmd);
		dir = ft_strjoin(dir, "/");
		if (access(bin, F_OK) == 0 && ft_strcmp(bin, dir) != 0)
		{
			free(dir);
			return (bin);
		}
		free_dir_bin(dir, bin);
		s += lendir + 1;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*retour;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
	{
		retour = ft_strdup(cmd);
		return (retour);
	}
	retour = get_path_scd(cmd, env[i] + 5);
	return (retour);
}

char	*ft_path(char **args, char **env)
{
	char	*path;

	path = NULL;
	if (!args || !args[0] || !env)
		return (NULL);
	if (new_slash(args[0]) == 1)
		path = ft_strdup(args[0]);
	else
		path = get_path(args[0], env);
	return (path);
}

char	**free_arg_path(char **args, char *path)
{
	int	i;

	i = 0;
	if (path)
		free (path);
	if (!args)
		return (NULL);
	if (args)
	{
		while (args[i])
		{
			if (args[i])
			{
				free(args[i]);
			}
			i++;
		}
		if (args)
			free(args);
	}
	args = NULL;
	path = NULL;
	return (NULL);
}
