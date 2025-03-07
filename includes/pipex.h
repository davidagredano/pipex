/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:37:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/07 17:29:39 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define EXIT_COMMAND_NOT_FOUND 127

# include <fcntl.h>    // open
# include <stdio.h>    // perror
# include <stdlib.h>   // free, exit, EXIT_FAILURE
# include <sys/wait.h> // wait
# include <unistd.h>   // access, execve, write

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
