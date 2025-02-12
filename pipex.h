/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:32:36 by jramos-a          #+#    #+#             */
/*   Updated: 2025/01/28 22:32:36 by jramos-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

char	*find_path(char *cmd, char **envp);
void	handle_no_env(char **envp);
void	execute_command(char *cmd, char **envp);
void	free_array(char **arr);
int		open_files(char **argv, int *infile, int *outfile);
char	*get_paths(char **envp);
void	child_process(int *fd, char **argv, char **envp);
void	parent_process(int *fd, char **argv, char **envp);
void	create_processes(int *fd, char **argv, char **envp);

#endif