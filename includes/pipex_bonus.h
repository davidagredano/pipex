/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:37:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/11 14:55:08 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define EXIT_COMMAND_NOT_FOUND 127

# include <fcntl.h>    // open
# include <stdio.h>    // perror
# include <stdlib.h>   // exit, free, EXIT_FAILURE
# include <sys/wait.h> // wait
# include <unistd.h>   // access, close, dup2, execve, fork, pipe, unlink

typedef struct s_cmd
{
	char	*filename;
	char	**argv;
	char	**envp;
}		t_cmd;

typedef struct t_hdoc
{
	char	*limiter;
	char	*filename;
}		t_hdoc;

typedef struct s_proc
{
	int		pipe_read_fd;
	int		pipe_write_fd;
	char	*infile;
	char	*outfile;
	char	*command_str;
}		t_proc;

typedef struct s_pipex
{
	int		processes_active;
	int		processes_count;
	t_proc	**processes;
	int		pipes_count;
	int		**pipes;
	int		heredoc_enabled;
	t_hdoc	*heredoc;
	char	**envp;
}		t_pipex;

/* Processes */
t_proc	**processes_create(int count);
void	processes_init(t_pipex *data, int argc, char *argv[]);
int		processes_wait(t_pipex *data, int *status);
void	processes_free(t_proc **processes);

/* Process */
void	process_redirect_stdin(t_pipex *data, t_proc *process);
void	process_redirect_stdout(t_pipex *data, t_proc *process);
void	process_execute(t_pipex *data, t_cmd *command);

/* Pipes */
int		**pipes_create(int n);
int		pipes_close(int **pipes);
void	pipes_free(int **pipes);

/* Heredoc */
t_hdoc	*heredoc_create(void);
int		heredoc_init(t_hdoc *heredoc, char *argv[]);
void	heredoc_free(t_hdoc *heredoc);

/* Command */
t_cmd	*command_create(t_pipex *data, t_proc *process);
void	command_free(t_cmd *command);

/* Utils */
int		pipex_perror_cleanup_exit(char *message, t_pipex *data, int status);
int		pipex_cleanup(t_pipex *data);
void	pipex_free(t_pipex *data);
void	process_perror_free_exit(char *message, t_pipex *data, int status);
void	strs_free(char **strs);
char	*get_next_line(int fd);

#endif
