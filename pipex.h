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

int parent_process(int *fd, char **argv, char **envp);
int child_process(int *fd, char **argv, char **envp);
int parse_args(int argc, char **argv);
void exit_error(char *msg);
void execute(char *cmd, char **envp);
char *find_path(char *cmd, char **envp);

#endif