/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:37:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/03 13:41:45 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h> // EXIT_FAILURE

typedef struct s_cmd
{
	char	*filename;
	char	**argv;
	char	**envp;
}	t_cmd;

/* Commands */
t_cmd	*cmd_process(char *cmd_str, char **envp);

/* Debug */
void	print_cmd(t_cmd *cmd);

#endif
