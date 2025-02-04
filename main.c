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

void	handle_errors(char **envp)
{
	handle_no_env(envp);
	handle_no_path();
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		infile;
	int		outfile;
	pid_t	pid2;

	if (argc != 5)
		exit_error("Pipex: infile command command outfile");
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
	waitpid(pid2, NULL, 0);
	waitpid(pid, NULL, 0);
	return (0);
}
