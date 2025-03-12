/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:37:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/08 12:52:49 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define EXIT_COMMAND_NOT_FOUND 127

# include <fcntl.h>    // open
# include <stdio.h>    // perror
# include <stdlib.h>   // exit, free, EXIT_FAILURE
# include <sys/wait.h> // wait
# include <unistd.h>   // access, close, dup2, execve, fork, pipe

typedef struct s_cmd
{
	char	*filename;
	char	**argv;
	char	**envp;
}		t_cmd;

/* Commands */
char	*command_get_filename(char *command_name, char **envp);
void	command_free(t_cmd *command);

/* Utils */
void	strs_free(char **strs);
void	cleanup_partial(int pipefd[2]);
int		cleanup(int pipefd[2]);
void	perror_exit(char *message, int status);

#endif
