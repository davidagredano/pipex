/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:37:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/04 13:08:55 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>  // perror
# include <stdlib.h> // free, exit, EXIT_FAILURE
# include <unistd.h> // access, execve

typedef struct s_cmd
{
	char	*filename;
	char	**argv;
	char	**envp;
}		t_cmd;

/* Commands */
t_cmd	*cmd_process(char *cmd_str, char **envp);
void	cmd_exec(t_cmd *cmd);
char	*cmd_get_filename(t_cmd *cmd);
void	cmd_free(t_cmd *cmd);
void	cmd_exit_error(t_cmd *cmd, const char *error_msg);

/* Utils */
void	free_strs(char **strs);

/* Debug */
void	print_cmd(t_cmd *cmd);

#endif
