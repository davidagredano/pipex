/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:37:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/08 10:30:11 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define EXIT_COMMAND_NOT_FOUND 127

# include <fcntl.h>    // open
# include <stdio.h>    // perror
# include <stdlib.h>   // exit, free, EXIT_FAILURE
# include <sys/wait.h> // waitpid
# include <unistd.h>   // access, close, dup2, execve, fork, pipe

typedef struct s_cmd
{
	char	*filename;
	char	**argv;
	char	**envp;
}		t_cmd;

/* Commands */
char	*cmd_get_filename(char *cmd_name, char **envp);
void	cmd_free(t_cmd *cmd);

/* Utils */
void	free_strs(char **strs);
int		cleanup(int pipefd[2], pid_t pids[2]);

/* Debug */
void	print_cmd(t_cmd *cmd);

#endif
