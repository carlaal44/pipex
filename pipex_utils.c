/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:04:00 by carfern2          #+#    #+#             */
/*   Updated: 2025/05/30 12:25:03 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	setup_child(int *fd)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
}

void	setup_parent(int *fd, int outfile_fd)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 outfile");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	close(outfile_fd);
}

char	**prepare_args(char *cmd)
{
	return ft_split(cmd, ' ');
}

int	open_outfile(char *outfile)
{
	int		outfile_fd;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		perror("open outfile");
		exit(1);
	}
	return (outfile_fd);
}

void	setup_parent_execution(t_pipex *data)
{
	char	**args;
	char	*cmd_path;
	int		len;

	args = prepare_args(data->cmd);
	cmd_path = get_executable_path(args[0]);
	if (!cmd_path)
	{
		write(2, "command not found: ", 19);
		len = 0;
		while (args[0][len])
			len++;
		write(2, args[0], len);
		write(2, "\n", 1);
		exit(127);
	}
	setup_parent(data->fd, data->outfile_fd);
	if (execve(cmd_path, args, data->envp) ==  -1)
	{
		perror("execve (parent)");
		free(cmd_path);
		exit(127); 
	}
}

