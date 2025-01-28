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
	char	*path;
	int		i;

	i = 0;
	// manejar no enviroment
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
	{
		if (i == 0)
			handle_no_path();
	}
	i++;
}

void handle_no_path(char **envp)
{
	int i;

	i = 0;
	if (ft_strnstr(envp[i], "PATH=", 5) == 0)
	{
		handle_no_env(envp);
		perror("Pipex: command not found: Path not set");
		exit(0);
	}
	i++;
}
// gestionar ruta absoluta
// manejar que el input contenga una barra
void handle_no_env(char **envp)
{
	if (envp == NULL)
	{
		perror("Pipex: command not found: Environment not set");
		exit(0);
	}
}

void execute_command(char *cmd, char **envp)
{
	char	**string_cmd;
	char	*path;

	string_cmd = ft_split(cmd, ' ');
	path = find_path(string_cmd[0], envp);
	//gestionar no path
	if (execve(path, string_cmd, envp) == -1)
	{
		ft_putstr_fd("Pipex: command not found: ", 2);
		ft_putendl_fd(string_cmd[0], 2);
		exit(0);
	}
}

void exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
