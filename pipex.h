/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:34:14 by marvin            #+#    #+#             */
/*   Updated: 2025/01/21 09:34:14 by marvin           ###   ########.fr       */
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