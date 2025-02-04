/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:37:17 by jramos-a          #+#    #+#             */
/*   Updated: 2025/01/29 12:45:07 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(char **argv, int *infile, int *outfile)
{
	*infile = open(argv[1], O_RDONLY);
	if (*infile == -1)
	{
		perror("Pipex: Error opening infile");
		*infile = open("/dev/null", O_RDONLY);
	}
	*outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile == -1)
		exit_error("Pipex: Error opening outfile");
	return (0);
}

int	parent_process(int *fd, char **argv, char **envp, int outfile)
{
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	dup2(outfile, 1);
	close(outfile);
	execute_command(argv[3], envp);
	return (0);
}

int	child_process(int *fd, char **argv, char **envp, int infile)
{
	dup2(infile, 0);
	close(infile);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	execute_command(argv[2], envp);
	return (0);
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

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		infile;
	int		outfile;
	pid_t	pid2;

	if (argc != 5)
		perror("Pipex: infile command command outfile");
	if (pipe(fd) == -1)
		exit_error("Pipex: Pipe error");
	open_files(argv, &infile, &outfile);
	pid = fork();
	pid2 = fork();
	if (pid == -1 || pid2 == -1)
		exit_error("Pipex: Fork error");
	if (pid == 0)
		child_process(fd, argv, envp, infile);
	if (pid2 == 0)
		parent_process(fd, argv, envp, outfile);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
