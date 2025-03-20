/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:04:00 by carfern2          #+#    #+#             */
/*   Updated: 2025/03/20 16:09:22 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	prepare_args(char *cmd, char **args)
{
	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
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
	char	*args[4];

	prepare_args(data->cmd, args);
	setup_parent(data->fd, data->outfile_fd);
	if (execv(args[0], args) == -1)
	{
		perror("execv (parent)");
		exit(127);
	}
}
