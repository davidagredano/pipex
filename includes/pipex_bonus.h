/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:37:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/11 12:51:00 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

typedef struct s_proc
{
	int		pipe_read_fd;
	int		pipe_write_fd;
	char	*infile;
	char	*outfile;
	char	*cmd_str;
}		t_proc;

typedef struct s_pipex
{
	int		processes_count;
	t_proc	**processes;
	int		pipes_count;
	int		**pipes;
	char	**envp;
	int		active_child_processes;
}		t_pipex;

/* Pipex */
t_pipex	*pipex_create(int argc, char *argv[], char *envp[]);
int		pipex_cleanup(t_pipex *data);
void	pipex_free(t_pipex *data);

/* Processes */
t_proc	**processes_create(int count);
void	processes_init(t_pipex *data, int argc, char *argv[]);
int		processes_wait(t_pipex *data, int *status);
void	processes_free(t_proc **processes);

/* Pipes */
int		**pipes_create(int n);
int		pipes_close(t_pipex *data);
void	pipes_free(int **pipes);

/* Commands */
char	*cmd_get_filename(char *cmd_name, char **envp);
void	cmd_free(t_cmd *cmd);

/* Utils */
void	free_strs(char **strs);
void	free_exit(t_pipex *data, int status);
void	free_perror_exit(t_pipex *data, char *message, int status);

/* Debug */
void	print_cmd(t_cmd *cmd);

#endif
