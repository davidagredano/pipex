#include "../includes/pipex.h"
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
