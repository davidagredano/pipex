#include "../includes/pipex.h"
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
