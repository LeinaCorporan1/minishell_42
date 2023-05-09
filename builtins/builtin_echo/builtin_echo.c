/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:35:57 by massavie          #+#    #+#             */
/*   Updated: 2023/02/23 08:51:37 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char *str, int fd, int nl)
{
	if (str)
		ft_putstr_fd(str, fd);
	if (nl == 1)
		ft_putstr_fd("\n", fd);
}

int	valid_echo(t_cmd *cmd, char *bufargs)
{
	int	outfile;

	outfile = 1;
	if (cmd->redirect.stdout != -2)
		outfile = cmd->redirect.stdout;
	if (!ft_strncmp(bufargs, "echo", ft_strlen("echo")))
	{
		if (!ft_strcmp(cmd->cmd, "echo"))
			return (builtin_echo(cmd, outfile), 0);
		if (cmd->cmd_quotes == 0 && ft_strlen(cmd->cmd) > ft_strlen("echo")
			&& !ft_strncmp(bufargs, "echo ", ft_strlen("echo ")))
			return (builtin_echo(cmd, outfile), 0);
		return (1);
	}
	return (0);
}

int	echo_newline_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			i++;
			while (str[i] && str[i] == 'n')
			{
				i++;
				if (str[i] == '\0' || !str[i])
					return (1);
			}
			if (str[i] != 'n')
				return (0);
			i++;
		}
		else
			return (0);
	}
	return (0);
}

char	*remove_quotes_echo(char *input, int wich)
{
	int		i;
	int		quotes;
	char	*to_return;

	i = 0;
	quotes = -1;
	to_return = NULL;
	while (input && input[i])
	{
		if (quotes_identi(input[i]) == wich && quotes == -1)
			quotes = i;
		if (quotes == -1 || (input[i] != input[quotes]))
		{
			to_return = ft_strjoin_char(to_return, input[i]);
		}
		i++;
	}
	return (to_return);
}

int	builtin_echo(t_cmd *cmd, int fd)
{
	char	*str;
	char	*removed;
	int		i;

	str = NULL;
	removed = NULL;
	i = -1;
	while (cmd->args && cmd->args[++i])
	{
		if (ft_atoi(cmd->args[i][1]) > 0)
		{
			removed = remove_quotes_echo \
			(cmd->args[i][0], ft_atoi(cmd->args[i][1]));
			str = ft_strjoin(str, removed);
			free(removed);
		}
		else
			str = ft_strjoin(str, cmd->args[i][0]);
	}
	if (cmd->cmd && ft_strlen(cmd->cmd) > 4 && (cmd->cmd[4] != '\0'
			|| cmd->cmd[5] != '\0')
		&& !ft_strncmp(cmd->cmd + 5, "-n", (int)ft_strlen("-n")))
		return (ft_echo(str, fd, 0), free(str), 1);
	return (ft_echo(str, fd, 1), free(str), 1);
}
