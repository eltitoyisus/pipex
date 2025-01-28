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

int	open_files(char **argv, int *infile, int *outfile)
{
	*infile = open(argv[1], O_RDONLY);
	if (*infile == -1)
		exit_error("Pipex: Error opening infile");
	*outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile == -1)
		exit_error("Pipex: Error opening outfile");
	return (0);
}

int	parent_process(int *fd, char **argv, char **envp, int outfile)
{
	dup2(fd[0], 0);
	close(fd[1]);
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

	if (argc != 5)
		exit_error("Pipex: infile command command outfile");
	if (pipe(fd) == -1)
		exit_error("Pipex: Pipe error");
	open_files(argv, &infile, &outfile);
	pid = fork();
	if (pid == -1)
		exit_error("Pipex: Fork error");
	if (pid == 0)
		child_process(fd, argv, envp, infile);
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(fd, argv, envp, outfile);
	}
	return (0);
}
