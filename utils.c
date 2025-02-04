/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:37:23 by jramos-a          #+#    #+#             */
/*   Updated: 2025/01/29 13:20:26 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;
	char	*temp;

	if (!envp || !*envp)
		return (cmd);
	for (i = 0; envp[i] && !ft_strnstr(envp[i], "PATH=", 5); i++);
	if (!envp[i])
		handle_no_path();
	if (!(paths = ft_split(envp[i] + 5, ':')))
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!access(full_path, X_OK))
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
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
	if (!split_cmd || !split_cmd[0])
	{
		ft_putstr_fd("Pipex: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		free_array(split_cmd);
		exit(0);
	}
	path = find_path(split_cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd("Pipex: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		free_array(split_cmd);
		exit(0);
	}
	execve(path, split_cmd, envp);
	perror("execve failed");
	free(path);
	free_array(split_cmd);
	exit(0);
}

void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
