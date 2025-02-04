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

char	*get_paths(char **envp)
{
	int	i;

	if (!envp || !*envp)
		handle_no_env(envp);
	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		handle_no_env(envp);
	if (envp[i])
		return (envp[i] + 5);
	else
		return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;
	char	*temp;

	paths = ft_split(get_paths(envp), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!access(full_path, X_OK))
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	handle_no_env(char **envp)
{
	if (envp == NULL || *envp == NULL)
	{
		exit_error("Pipex: command not found: Environment not set");
		exit(0);
	}
}

void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
