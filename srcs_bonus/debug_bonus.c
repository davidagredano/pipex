#include "../includes/pipex_bonus.h"
#include "../libft/libft.h"

void	print_cmd(t_cmd *cmd)
{
	char	**argv_ptr;

	ft_putstr("cmd->filename: ");
	ft_putendl_fd(cmd->filename, STDOUT_FILENO);
	ft_putstr("cmd->argv: ");
	argv_ptr = cmd->argv;
	while (*argv_ptr)
	{
		ft_putstr(*argv_ptr);
		argv_ptr++;
		if (*argv_ptr)
			ft_putstr(", ");
	}
	ft_putstr("\n\n");
}

void	print_processes(t_proc **processes)
{
	int	i;

	i = 0;
	while (processes[i])
	{
		printf("processes[%d]\n", i);
		printf("- pipe_read:  %d\n", processes[i]->pipe_read_fd);
		printf("- pipe_write: %d\n", processes[i]->pipe_write_fd);
		printf("- infile:     %s\n", processes[i]->infile);
		printf("- outfile:    %s\n", processes[i]->outfile);
		printf("- cmd_str:    %s\n\n", processes[i]->cmd_str);
		i++;
	}
}

void	print_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		printf("pipes[%d]={ %d, %d }\n", i, pipes[i][0], pipes[i][1]);
		i++;
	}
}
