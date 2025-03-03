/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:28:06 by dagredan          #+#    #+#             */
/*   Updated: 2025/03/03 14:02:25 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../libft/libft.h"

static int	count_words(char *str)
{
	int		n;

	n = 0;
	while (str && *str != '\0')
	{
		if (*str == ' ')
			str++;
		else
		{
			n++;
			str = ft_strchr(str, ' ');
		}
	}
	return (n);
}

static char	**cmd_get_argv(char *cmd_str)
{
	char	**argv;
	char	*token;
	int		i;

	argv = ft_calloc(count_words(cmd_str) + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	token = ft_strtok(cmd_str, " ");
	while (token)
	{
		argv[i] = token;
		token = ft_strtok(NULL, " ");
		i++;
	}
	return (argv);
}

t_cmd	*cmd_process(char *cmd_str, char **envp)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->filename = "filename";
	cmd->argv = cmd_get_argv(cmd_str);
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	cmd->envp = envp;
	return (cmd);
}
