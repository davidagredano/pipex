/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/04 13:09:17 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;

	if (argc != 5)
		return (EXIT_FAILURE);
	if (access(argv[1], R_OK) == -1)
	{
		perror(argv[1]);
		return (EXIT_FAILURE);
	}
	cmd1 = cmd_process(argv[2], envp);
	cmd2 = cmd_process(argv[3], envp);
	cmd_exec(cmd1);
	cmd_exec(cmd2);
	cmd_free(cmd1);
	cmd_free(cmd2);
}
