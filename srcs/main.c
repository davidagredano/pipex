/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:53:33 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/03 13:51:58 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;

	if (argc != 5)
		return (EXIT_FAILURE);
	cmd1 = cmd_process(argv[2], envp);
	if (!cmd1)
		return (1);
	cmd2 = cmd_process(argv[3], envp);
	if (!cmd2)
	{
		free(cmd1);
		return (1);
	}
	print_cmd(cmd1);
	print_cmd(cmd2);
}
