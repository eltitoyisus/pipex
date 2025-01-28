/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:37:17 by jramos-a          #+#    #+#             */
/*   Updated: 2025/01/28 08:37:17 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
int parse_args(int argc, char **argv)
{
	int fd;
	int infile;
	int outfile;

	if (argc != 5)
		exit_error("Invalid number of arguments");
	// gestionar si open falla
	infile = open(argv[1], O_RDONLY); // infile
	if (infile == -1)
		exit_error("Error opening file");
	// grstionar si open falla
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); // outfile
	if (outfile == -1)
		exit_error("Error opening file");
	return (0);
} */

int parent_process(int *fd, char **argv, char **envp)
{
	dup2(fd[1], 1);
	close(fd[1]);
	execute(argv[3], envp);
	return (0);
}

int child_process(int *fd, char **argv, char **envp)
{
	int file_fd;

	file_fd = open(argv[1], O_RDONLY);
	if (file_fd == -1)
		exit_error("Pipex: Error opening file");
	dup2(fd[1], 1);
	close(fd[1]);
	close(file_fd);
	execute(argv[2], envp);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
		exit_error("Pipex: Pipe error");
	pid = fork();
	if (pid == -1)
		exit_error("Pipex: Fork error");
	if (pid == 0)
		child_process(fd, argv, envp);
	else
		parent_process(fd, argv, envp);
	return (0);
}
