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

void	exit_error(char *msg);
char	*find_path(char *cmd, char **envp);
void	handle_no_path(void);
void	handle_no_env(char **envp);
void	handle_errors(char **envp);
void	execute_command(char *cmd, char **envp);
int		parent_process(int *fd, char **argv, char **envp, int outfile);
int		child_process(int *fd, char **argv, char **envp, int infile);
int		open_files(char **argv, int *infile, int *outfile);

#endif