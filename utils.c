/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:37:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/01/28 08:37:23 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!envp || !*envp)
		return (cmd);
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		handle_no_path();
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	handle_no_path(void)
{
	exit_error("Pipex: command not found: Path not set");
	exit(0);
}

void	handle_no_env(char **envp)
{
	if (envp == NULL || *envp == NULL)
	{
		exit_error("Pipex: command not found: Environment not set");
		exit(0);
	}
}

void	execute_command(char *cmd, char **envp)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path = find_path(split_cmd[0], envp);
	if (execve(path, split_cmd, envp) == -1)
	{
		ft_putstr_fd("Pipex: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		exit(0);
	}
}

void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
