/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:37:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/18 13:55:53 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define EXIT_PERMISSION_DENIED 126
# define EXIT_COMMAND_NOT_FOUND 127

# include <fcntl.h>    // open
# include <stdio.h>    // perror
# include <stdlib.h>   // exit, free
# include <sys/wait.h> // waitpid
# include <unistd.h>   // access, close, dup2, execve, fork, pipe, unlink

typedef struct t_hdoc
{
	char	*limiter;
	char	*filename;
}		t_hdoc;

typedef struct s_cmd
{
	char	*filename;
	char	**argv;
	char	**envp;
}		t_cmd;

typedef struct s_proc
{
	pid_t	pid;
	int		pipe_read_fd;
	int		pipe_write_fd;
	char	*infile;
	char	*outfile;
	char	*command_str;
	t_cmd	*command;
}		t_proc;

typedef struct s_pipex
{
	int		processes_count;
	t_proc	**processes;
	int		**pipes;
	int		heredoc_enabled;
	t_hdoc	*heredoc;
	char	**envp;
}		t_pipex;

/* Processes */
void	processes_create(t_pipex *data, int count);
void	processes_init(t_pipex *data, int argc, char *argv[]);
int		processes_wait(t_pipex *data, int *status);
void	processes_free(t_proc **processes);

/* Process */
void	process_redirect_stdin(t_pipex *data, t_proc *process);
void	process_redirect_stdout(t_pipex *data, t_proc *process);
void	process_execute(t_pipex *data, t_proc *process);

/* Pipes */
void	pipes_create(t_pipex *data, int count);
int		pipes_destroy(t_pipex *data);

/* Heredoc */
void	heredoc_create(t_pipex *data, int is_here_doc);
void	heredoc_init(t_pipex *data, char *argv[]);
void	heredoc_read_stdin(t_pipex *data);
void	heredoc_free(t_hdoc *heredoc);

/* Command */
t_cmd	*command_create(t_pipex *data, t_proc *process);
void	command_free(t_cmd *command);

/* Utils */
void	child_cleanup_exit(t_pipex *data, char *error_message, int exit_status);
void	parent_cleanup_exit(t_pipex *data, char *message);
int		parent_cleanup(t_pipex *data);
void	pipex_free(t_pipex *data);
void	strs_free(char **strs);

#endif
