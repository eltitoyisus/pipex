/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:37:17 by jramos-a          #+#    #+#             */
/*   Updated: 2025/02/17 11:14:29 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *fd, char **argv, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
	{
		perror("Pipex: Error opening infile");
		infile = open("/dev/null", O_RDONLY);
	}
	dup2(infile, 0);
	close(infile);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	execute_command(argv[2], envp);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror("Pipex: Error opening outfile");
		exit(0);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	dup2(outfile, 1);
	close(outfile);
	execute_command(argv[3], envp);
}

void	create_processes(int *fd, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		perror("Pipex: Fork error");
	if (pid1 == 0)
		child_process(fd, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		perror("Pipex: Fork error");
	if (pid2 == 0)
		parent_process(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];

	if (argc != 5)
	{
		write(1, "Pipex: infile command command outfile", 37);
		exit(1);
	}
	if (pipe(fd) == -1)
		perror("Pipex: Pipe error");
	create_processes(fd, argv, envp);
	return (0);
}
