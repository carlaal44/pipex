/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:06:54 by carfern2          #+#    #+#             */
/*   Updated: 2025/02/13 16:10:59 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	setup_child(int *fd)
{
	int		status;

	status = dup2(fd[1], STDOUT_FILENO);
	if (status == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd[0]);
}

void	execute_child(int *fd, char **envp)
{
	pid_t	pid;
	char	*cmd[3];

	write(1, "Exxecuting child process\n", 24);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		write(1, "Inside child process\n", 22);
		setup_child(fd);
		cmd[0] = "/bin/ls";
		cmd[1] = "-l";
		cmd[2] = NULL;
		if (execve(cmd[0], cmd, envp) == -1)
		{
			perror("execve (child)");
			exit(1);
		}
	}
}

void	execute_parent(int *fd, char **envp)
{
	int		status;
	char	*cmd2[3];

	write(1, "Waiting for child process\n", 27);
	wait(NULL);
	write(1, "Executing parent process\n", 26);
	status = dup2(fd[0], STDIN_FILENO);
	if (status == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	cmd2[0] = "/bin/ls";
	cmd2[1] = "-l";
	cmd2[2] = NULL;
	if (execve(cmd2[0], cmd2, envp) == -1)
	{
		perror("execve (parent)");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];

	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 \"command1\" \"command2\" file2\n", 50);
		return (1);
	}
	create_pipe(fd);
	execute_child(fd, envp);
	execute_child(fd, envp);
	return (0);
}
