/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carfern2 <carfern2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:06:54 by carfern2          #+#    #+#             */
/*   Updated: 2025/05/30 12:22:38 by carfern2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}
static void child_exec(char *cmd, char **envp, int *fd, int infile_fd)
{
    char **args;
    char *cmd_path;

    args = prepare_args(cmd);
    if (!args)
        exit(1);
    cmd_path = get_executable_path(args[0]);
    if (!cmd_path)
    {
        write(2, "command not found: ", 19);
        write(2, args[0], ft_strlen(args[0]));
        write(2, "\n", 1);
        exit(127);
    }
    dup2(infile_fd, STDIN_FILENO);
    close(infile_fd);
    setup_child(fd);
    if (execve(cmd_path, args, envp) == -1)
    {
        perror("execve (child)");
        free(cmd_path);
        exit(1);
    }
}
void execute_child(int *fd, char *cmd, char **envp, int infile_fd)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
        child_exec(cmd, envp, fd, infile_fd);
}

void	execute_parent(t_pipex *data, char *outfile)
{
	wait(&data->status);
	data->outfile_fd = open_outfile(outfile);
	if (fork() == 0)
		setup_parent_execution(data);
	close(data->fd[0]);
	close(data->fd[1]);
	close(data->outfile_fd);
	close(data->infile_fd);
	wait(&data->status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		data;

	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 \"command1\" \"command2\" file2\n", 50);
		return (1);
	}
	data.envp = envp;
	data.cmd = argv[3];
	data.infile_fd = open(argv[1], O_RDONLY);
	if (data.infile_fd < 0)
	{
		perror("open infile");
		exit(1);
	}
	create_pipe(data.fd);
	execute_child(data.fd, argv[2], envp, data.infile_fd);
	execute_parent(&data, argv[4]);
	return (WEXITSTATUS(data.status));
}
