#include "../includes/pipex_bonus.h"
#include "../libft/libft.h"

void	print_command(t_cmd *command)
{
	char	**argv_ptr;

	ft_putstr("command->filename: ");
	ft_putendl_fd(command->filename, STDOUT_FILENO);
	ft_putstr("command->argv: ");
	argv_ptr = command->argv;
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
		printf("- command_str:    %s\n\n", processes[i]->command_str);
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

static void	print_heredoc(t_hdoc *heredoc)
{
	printf("heredoc->filename: %s\n", heredoc->filename);
	printf("heredoc->limiter:  %s\n", heredoc->limiter);
}

void	print_pipex(t_pipex *data)
{
	int	i;

	printf("data->processes_count: %d\n", data->processes_count);
	printf("data->pipes_count: %d\n", data->pipes_count);
	printf("data->heredoc_enabled: %d\n", data->heredoc_enabled);
	printf("data->processes_active: %d\n", data->processes_active);
	printf("data->envp:\n");
	i = 0;
	while (data->envp[i])
	{
		printf("envp[%d]: %s\n", i, data->envp[i]);
		i++;
	}
	printf("\n");
	if (data->heredoc_enabled)
		print_heredoc(data->heredoc);
	print_processes(data->processes);
	print_pipes(data->pipes);
}
